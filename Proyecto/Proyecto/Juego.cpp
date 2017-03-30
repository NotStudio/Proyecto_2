#include "Juego.h"
#include "Tostadora.h"
#include "Camara.h"
#include "Play.h"
#include "checkML.h"
#include "HUD.h"
#include <io.h>
#include "recorreFicheros.h"
#include <SDL_events.h>
#include "MenuPG.h"
#include "ZonaAccion.h"
#include "ZonaBase.h"

void operator+=(vector<string>& e,vector<string> o){
	for (size_t i = 0; i < o.size(); i++)
	{
		e.push_back(o[i]);
	}
}
// Constructora que inicializa todos los atributos de la clase Juego
Juego::Juego(b2World* mundo) : error(false), gameOver(false), exit(false), score(0), world(mundo)
{
	window.alto = 600; //Tamaño de la ventana.
	window.ancho = 800;
	fondoRect.x = 0; //Posición y tamaño de la ventana.
	fondoRect.y = 0;
	fondoRect.w = window.ancho;
	fondoRect.h = window.alto;
	//iniciazión de SDL
	if (!initSDL()) {
		error = true;
		std::cout << "Ha ocurrido un error con SDL";
	}
	//Esto es el wall de mexico los estados hundidos

	//Añadimos al vector del nombre de las texturas los nombres de las imágenes. Tienen que tener un orden concreto.
	//Primero El idle, para cualquier animacion
	//Tostadora
	nombreTexturas = Buscador(TiposArchivo::PNG);
	//Tipografias
	ubicacionTipografias = Buscador(TiposArchivo::TTF);

	UbicacionSonidos = Buscador(TiposArchivo::WAV);
	UbicacionSonidos += Buscador(TiposArchivo::MP3);
	world->SetContactListener(&listener);
	


	//Arrancamos las texturas y los objetos.
	initMedia();
	initHabitaciones();
	//inicializamos los punteros a nullptr porque el estado play es el que hace new.
	Camera = nullptr;
	personaje = nullptr;
	zona = nullptr;

	pushState(new MenuPG(this));
	cambiarMusica("Exodus");
	run();
	
}

Juego::Juego()
{
	world = nullptr;

}
Juego::~Juego()
{

	//Liberamos los objetos.
	freeMedia();
	
	//Liberamos SDL.
	closeSDL();
	pWindow = nullptr;
	pRenderer = nullptr;

	//Liberar estados
	while (!estados.empty()){
		popState();
	}
	//Liberar cosas de la Física
	//Borrar la camara? delete camera;
	
	
	
}


void Juego::cambiarMusica(string id)
{
	if (Mix_PlayingMusic()==0) {
		MusicaActual = cargarMusica(id);
		Mix_PlayMusic(MusicaActual, -1);
	}
	else {
		Mix_FadeOutMusic(1200);
		MusicaSig=cargarMusica(id);
		timerCambio = SDL_AddTimer(1500, timerMus, this);
	}
}

//Devolvemos una textura en función del enumerado que nos pasen.
TexturasSDL* Juego::getTextura(const string &entity, const string &anim) {
	try{
		return mapTexturas.at(entity).at(anim);
	}
	catch (out_of_range){
		std::cout << "Error al cargar textura";
	}
	
	
};
//Devolvemos el puntero al Render que está como atributo en la clase.
SDL_Renderer* Juego::getRender() const {

	return pRenderer;

};

//Devolvemos la posición actual del mouse, que se actualiza en el onClick.
void Juego::getMousePos(int &mpx, int &mpy)const {

	mpx = mousePos.x;
	mpy = mousePos.y;

};
//Método que inicializa las texturas.
void Juego::initMedia() {
	
	//Creamos las texturas y las metemos en el vector de punteros.
	for (int i = 0; i < nombreTexturas.size(); i++) {

		std::string entity, anim, aux;
		aux = nombreTexturas[i];
		entity = aux.substr(aux.find_last_of('/') + 1);
		anim = aux.substr(aux.find_last_of('_')+1);
		entity.erase(entity.find_last_of('_'));		
		anim.erase(anim.find_last_of('.'));
		try{
			mapTexturas.at(entity);//Para que no cree la textura dos veces.
			mapTexturas.at(entity).emplace(std::make_pair(anim, new TexturasSDL));
			mapTexturas.at(entity).at(anim)->load(pRenderer, aux);

		}
		catch(out_of_range){

			unordered_map<string, TexturasSDL*> auxMap;
			mapTexturas.emplace(std::make_pair(entity, auxMap));
			mapTexturas.at(entity).emplace(std::make_pair(anim, new TexturasSDL));
			mapTexturas.at(entity).at(anim)->load(pRenderer, aux);
		}
		
	}
	for (size_t i = 0; i < ubicacionTipografias.size(); i++)
	{
		string tipograf = ubicacionTipografias[i].substr( ubicacionTipografias[i].find_last_of('/')+1);
		tipograf.erase(tipograf.find_last_of('.'));
		try
		{
			fuentes.at(tipograf);
		}
		catch (out_of_range)
		{
			unordered_map<int, Fuente*> auxMap;
			fuentes.emplace(std::make_pair(tipograf, auxMap));
			fuentes.at(tipograf).emplace(std::make_pair(50, new Fuente()));
			fuentes.at(tipograf).at(50)->loadFuente(ubicacionTipografias[i]);
		}
	}
	for (size_t i = 0; i < UbicacionSonidos.size(); i++)
	{
		string id = UbicacionSonidos[i];
		id = id.substr(id.find_last_of("/") + 1);
		id = id.erase(id.find_last_of("."));
		int o = UbicacionSonidos[i].find("Efectos");
		if (o>0) {
			Efectos.emplace(make_pair(id, nullptr));
			Efectos.at(id)= Mix_LoadWAV(UbicacionSonidos[i].c_str());
			if(!Efectos.at(id))
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else {
			Musica.emplace(make_pair(id, nullptr));
			Musica.at(id) = Mix_LoadMUS(UbicacionSonidos[i].c_str());
			if (!Musica.at(id))
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
};

void Juego::initHabitaciones(){
	vector<string> ficherosPatronesEnemigos = Buscador(TiposArchivo::ENEPAT);
	vector<string> ficherosPatronesInanimados = Buscador(TiposArchivo::INAPAT);
	vector<string> ficherosHabitaciones = Buscador(TiposArchivo::CSV);
	for (size_t i = 0; i < ficherosHabitaciones.size(); i++)
	{
		string id = ficherosHabitaciones[i].substr(ficherosHabitaciones[i].find_last_of('/') + 1);
		id.erase(id.find_last_of('.'));		
		if (id == "Base"){
			base = RoomInfo(ficherosHabitaciones[i]);
		}
		else
			Habitaciones.emplace(make_pair(id, RoomInfo(ficherosHabitaciones[i])));
	}
	for (size_t i = 0; i < ficherosPatronesEnemigos.size(); i++)
	{
		string id = ficherosPatronesEnemigos[i].substr(ficherosPatronesEnemigos[i].find_last_of('/') + 1);
		id.erase(id.find_last_of('.'));
		if (id == "Base") base.setPatronEnemigos(ficherosPatronesEnemigos[i]);
		else {
			try {
				Habitaciones.at(id).setPatronEnemigos(ficherosPatronesEnemigos[i]);
			}
			catch (out_of_range) {}
		}
	}
	for (size_t i = 0; i < ficherosPatronesInanimados.size(); i++)
	{
		string id = ficherosPatronesInanimados[i].substr(ficherosPatronesInanimados[i].find_last_of('/') + 1);
		id.erase(id.find_last_of('.'));
		if (id == "Base") base.setPatronInanimados(ficherosPatronesInanimados[i]);
		else {
			try {
				Habitaciones.at(id).setPatronInanimados(ficherosPatronesInanimados[i]);
			}
			catch (out_of_range) {}
		}
	}


}
//Método que libera las texturas.
void Juego::freeMedia() {

	std::unordered_map<string, std::unordered_map<string, TexturasSDL*>>::iterator it = mapTexturas.begin();

	while (it != mapTexturas.end()) {
		std::unordered_map<string, TexturasSDL*>::iterator itAux = mapTexturas.at(it->first).begin();
		while (itAux != mapTexturas.at(it->first).end()){
			delete mapTexturas.at(it->first).at(itAux->first);
			mapTexturas.at(it->first).at(itAux->first) = nullptr;
			itAux++;
		}
		
		it++;
	}
	
	unordered_map<string, unordered_map<int, Fuente*>>::iterator j=fuentes.begin();
	while (j != fuentes.end()) {
		unordered_map<int, Fuente* >::iterator e = fuentes.at(j->first).begin() ;
		while (e != fuentes.at(j->first).end())
		{
			delete fuentes.at(j->first).at(e->first);
			fuentes.at(j->first).at(e->first) = nullptr;
			e++;
		}
		j++;
	}
	
	for (unordered_map<string, Mix_Chunk*>::iterator itX = Efectos.begin(); itX != Efectos.end(); itX++)
	{
		Mix_FreeChunk(Efectos.at(itX->first));
		Efectos.at(itX->first) = nullptr;
	}
	
	for (unordered_map<string, Mix_Music *>::iterator itX = Musica.begin(); itX != Musica.end(); itX++)
	{
		Mix_FreeMusic(Musica.at(itX->first));
		Musica.at(itX->first) = nullptr;
	}

	//Esto debe ir en otro metodo
	for (int i = 0; i < objetos.size(); i++) {
		delete objetos[i];
		objetos[i] = nullptr;
	}
	//Esto debe ir en otro metodo
	for (int i = 0; i < objetos.size(); i++) {
		delete objetos[i];
		objetos[i] = nullptr;
	}
};
//Método que inicializa SDL
bool Juego::initSDL() {

	bool success = true; //Initialization flag

						 //Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_TIMER) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		if (TTF_Init() == -1) {
			cout << "onichan";
		}
		if (IMG_Init(IMG_INIT_PNG)==-1) {
			cout << "kek";
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			cout << "kek";
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("NOT A STUDIO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.ancho, window.alto, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';	
			success = false;
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
			//SDL_SetRenderDrawColor(pRenderer, 100, 126, 97, 255); //Set background color to black 
			SDL_SetRenderDrawColor(pRenderer, 0, 0,0 , 255); //Set background color to black 

			if (pRenderer == nullptr) {
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}
	return success;
};
//Método que libera SDL
void Juego::closeSDL() {

	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
};

//Método que maneja el array de botones, y los activa y desactiva segun el input.
bool Juego::handle_event() {

	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		switch (evento.type) {
		case SDL_QUIT:
			salir(); 
			break;
		case SDL_KEYDOWN:
			if (!KEYS[evento.key.keysym.scancode].mantenida)
				KEYS[evento.key.keysym.scancode].presionada = true;
			KEYS[evento.key.keysym.scancode].mantenida = true;
			break;
		case SDL_KEYUP:
			KEYS[evento.key.keysym.scancode].presionada = false;
			KEYS[evento.key.keysym.scancode].mantenida = false;
			break;
		case SDL_TEXTINPUT:
			break;
		case SDL_MOUSEMOTION:
			mousePos.x= evento.motion.x;
			mousePos.y = evento.motion.y;
			break;
		default:
			break;
		}
	} 
	return true;
};

//Método de consulta de la variable de control 'error'.
bool Juego::getError() {	return error;};
//Método que cierra el juego activando el booleano 'exit'
void Juego::salir() {	exit = true;}


//Update del juego, que llama al update de la camara y del estado
void Juego::update(){
	topState()->update();
	
}
//Draw del juego, llama al dibujar del estado y del HUD
void Juego::draw(){
	
	SDL_RenderClear(pRenderer);
	topState()->draw();
	
	SDL_RenderPresent(pRenderer);	

}

//Bucle principal del juego
void Juego::run() {
	
	int contSeg= 0;
	int fpsCount = 0;
	int lasssst = 0;
	bool stop = false;
	cout << "PLAY \n";
	lastUpdate = SDL_GetTicks();
	world->Step(1.0f / 60.0f, 6, 2);
	draw();
	handle_event();
	while (!exit) {
		handle_event();
		if (SDL_GetTicks() - lastUpdate >= MSxUpdate) {
			update();
			lastUpdate = SDL_GetTicks();
			fpsCount++;
		}
		world->Step(1.0f / 60.0f, 6, 2);
		draw();
		contSeg = SDL_GetTicks();
	}
	if (exit) cout << "EXIT \n";
	else if (gameOver) {
		cout << "GAME OVER \n";
	}
}

//MÉTODOS DE CONTROL DE MÁQUINA DE ESTADOS.
EstadoJuego* Juego::topState(){
	return estados.top();
}

void Juego::changeState(EstadoJuego* newState){

	popState();
	pushState(newState);
}

void Juego::pushState(EstadoJuego* newState){
	estados.push(newState);
}

void Juego::popState(){

	delete topState();
	estados.pop();
}


//Método de consulta de botón pulsado. Devuelve true si el botón que pasamos por parametro está pulsado.
bool Juego::inputQuery(int numButton) {
	return KEYS[numButton].mantenida;
}

//Metodo que te devuelve si la tecla ha sido pulsada por primera vez
bool Juego::teclaPulsada(int numButton) {
	if (KEYS[numButton].presionada) {
		KEYS[numButton].presionada = false;
		return true;
	}
	else
		return KEYS[numButton].presionada;
}

//Retornamos el mundo físico
b2World* Juego::getWorld() {
	return world;
}

//Metodo que controla el cambio de zona (zonaJugable-Base)
void Juego::setZona(std::string zonaNombre) {


	if (zona != nullptr)
		delete zona;
	if (zonaNombre == "ZonaAccion")
		zona = new ZonaAccion(this);
	else
		zona = new ZonaBase(this);
	
}

TexturasSDL* Juego::getTilesheet(Zona* z) {
	try
	{
		return mapTexturas.at("Tileset").at(static_cast<ZonaJuego*>(z)->getId()); 
	}
	catch (out_of_range)
	{
		printf("El tileset que has pedido no existe toma este por defecto \n");
		return mapTexturas.at("Tileset").begin()->second;
	}
}