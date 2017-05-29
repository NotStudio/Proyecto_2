#include "Juego.h"
#include "Tostadora.h"
#include "Camara.h"
#include "Play.h"
#include "Pausa.h"
#include "checkML.h"
#include "HUD.h"
#include <io.h>
#include "recorreFicheros.h"
#include <SDL_events.h>
#include "MenuPG.h"
#include "Cambio.h"
#include "GameOver.h"
#include "HUDinventory.h"
#include "MenuFinDeZona.h"

#include "Inanimado.h"
#include "ZonaTutorial.h"//Constructora que inicializa todos los atributos de la clase Juego


#include "ZonaDesguace.h"
#include "ZonaBosque.h"
#include "ZonaBase.h"
#include "ZonaPinApple.h"
#include <SDL_thread.h>
#include <iostream>
#include <fstream>
bool load = false;

void operator+=(vector<string>& e,vector<string> o){
	for (size_t i = 0; i < o.size(); i++)
	{
		e.push_back(o[i]);
	}
}
int threadFunction(void* data) { //Print incoming data
	system("start loading.exe");
	while (!load)
	{

	}
	system("taskkill /IM loading.exe >nul");
	return 0; 
}
// Constructora que inicializa todos los atributos de la clase Juego
Juego::Juego(b2World* mundo) : error(false), gameOver(false), exit(false), score(0), world(mundo)
{
	int data = 9;
	
	window.alto = 720; //Tamaño de la ventana.
	window.ancho = 1080;
	fondoRect.x = 0; //Posición y tamaño de la ventana.
	fondoRect.y = 0;
	fondoRect.w = window.ancho;
	fondoRect.h = window.alto;
	//iniciazión de SDL
	if (!initSDL()) {
		error = true;
		std::cout << "Ha ocurrido un error con SDL";
	}
	SDL_Thread* threadID = SDL_CreateThread(threadFunction, "LazyThread", nullptr);
	
	
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
	//b2_maxTranslation
	


	//Arrancamos las texturas y los objetos.
	initMedia();
	initHabitaciones();
	//inicializamos los punteros a nullptr porque el estado play es el que hace new.
	Camera = nullptr;
	personaje = nullptr;
	
	zona = nullptr;
	nave = nullptr;
	progresoNave = 0;
	
	//Cargar baul de un metodo leyendo de texto o de donde se guarde
	inventario = new Inventory(3, getTipografia("Acme____", 30), getRender());
	baul = new Inventory(100, getTipografia("Acme____", 30), getRender());



	tarjetasRecogidas = 0;

	Mix_Volume(-1,volumen);
	Mix_VolumeMusic(volumen);
	cargarJuego();
	load = true;
	pushState(new MenuPG(this));
	
	run();
	
}

Juego::Juego()
{
	world = nullptr;

}
Juego::~Juego()
{
	delete inventario;
	delete baul;
	//Liberamos los objetos.
	freeMedia();
	
	//Liberamos SDL.
	closeSDL();
	pWindow = nullptr;
	pRenderer = nullptr;

	//Liberar estados
	freeEstadoss();
	/*while (!estados.empty()){
		popState();
	}*/
	//Liberar cosas de la Física
	//Borrar la camara? delete camera;
	
	
	
}
void Juego::changeProgresoNave(){
	progresoNave++;
	if (progresoNave > 4)
		progresoNave = 4;
	string s = "NaveFase" + to_string(progresoNave);
	static_cast<NaveJuego*>(nave)->changeTexture(s);
}
void Juego::tarjetasRecogida(){
	
	tarjetasRecogidas++;
	string s = "SD " + to_string(tarjetasRecogidas);
	
	mem.at(s) = true;

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
			else {
				if(!id.find("Battle")) 
					MusicaBatalla.push_back(Musica.at(id));
			}
		}
	}
};

void Juego::initHabitaciones(){
	vector<string> ficherosTMX = Buscador(TiposArchivo::TMX);
	for (auto file : ficherosTMX) {
		string id = file.substr(file.find_last_of('/') + 1);
		id.erase(id.find_last_of('.'));
		string type = id;
		type = type.substr(0, type.find_first_of('_'));
		if (type != "Base") {
			if (type == "Map") {
				try
				{
					Habitaciones.at(id);
					printf("nombre repetido en el fichero %s \n", file);
				}
				catch (out_of_range)
				{
					Habitaciones.emplace(make_pair(id, nullptr));
					Habitaciones.at(id) = new TMXReader::MapData(file);
				}
			}
			else if (type == "MapIni") {
				try
				{
					HabitacionesIni.at(id);
					printf("nombre repetido en el fichero %s \n", file);
				}
				catch (out_of_range)
				{
					HabitacionesIni.emplace(make_pair(id, nullptr));
					HabitacionesIni.at(id) = new TMXReader::MapData(file);
				}

			}
			else if (type == "MapFin") {
				try
				{
					HabitacionesFin.at(id);
					printf("nombre repetido en el fichero %s \n", file);
				}
				catch (out_of_range)
				{
					HabitacionesFin.emplace(make_pair(id, nullptr));
					HabitacionesFin.at(id) = new TMXReader::MapData(file);
				}

			}
			else if (type == "MapBoss") {

				try
				{
					HabitacionesBoss.at(id);
					printf("nombre repetido en el fichero %s \n", file);
				}
				catch (out_of_range)
				{
					HabitacionesBoss.emplace(make_pair(id, nullptr));
					HabitacionesBoss.at(id) = new TMXReader::MapData(file);
				}
			}
			else if (type == "Tutorial") {
				if(HabitacionTutorial == nullptr)
					HabitacionTutorial = new TMXReader::MapData(file);
			}
		
		}
		else {
			Base = new TMXReader::MapData(file);
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
	//Borramos los niveles normales
	for (unordered_map<string,TMXReader::MapData*>::iterator i = Habitaciones.begin(); i !=Habitaciones.end(); i++)
	{
		delete Habitaciones.at(i->first);
		Habitaciones.at(i->first)=nullptr;
	}
	//Borrarmos los niveles iniciales
	for (unordered_map<string, TMXReader::MapData*>::iterator i = HabitacionesIni.begin(); i != HabitacionesIni.end(); i++)
	{
		delete HabitacionesIni.at(i->first);
		HabitacionesIni.at(i->first) = nullptr;
	}
	//Borramos los niveles finales
	for (unordered_map<string, TMXReader::MapData*>::iterator i = HabitacionesFin.begin(); i != HabitacionesFin.end(); i++)
	{
		delete HabitacionesFin.at(i->first);
		HabitacionesFin.at(i->first) = nullptr;
	}
	//Borramos los niveles de boses
	for (unordered_map<string, TMXReader::MapData*>::iterator i = HabitacionesBoss.begin(); i != HabitacionesBoss.end(); i++)
	{
		delete HabitacionesBoss.at(i->first);
		HabitacionesBoss.at(i->first) = nullptr;
	}

	delete HabitacionTutorial;
	HabitacionTutorial = nullptr; 

	delete Base;
	Base = nullptr;
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
		pWindow = SDL_CreateWindow("NOT A STUDIO", 0, 0,100, 100, SDL_WINDOW_SHOWN);
		SDL_SetWindowBordered(pWindow, SDL_FALSE);
		SDL_MaximizeWindow(pWindow);
		//SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
		if (pWindow == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';	
			success = false;
		}
		else {
		
			
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 100, 126, 97, 255); //Set background color to black 
			SDL_SetRenderDrawColor(pRenderer, 0, 0,0 , 150); //Set background color to black 
			SDL_RenderClear(pRenderer);
			SDL_RenderPresent(pRenderer);
			int ancho = 0, alto = 0;
			SDL_GetWindowSize(pWindow, &ancho, &alto);
			window.alto = alto;
			window.ancho = ancho;

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
			if (evento.key.keysym.sym == SDLK_ESCAPE){
				EstadoJuego* estado = topState();
				if (typeid(*estado) == typeid(Play)){
					changeState(new Pausa(this));
				}
			}
			else if (evento.key.keysym.sym == SDLK_i){
				changeInventory();
			}
			else if (evento.key.keysym.sym == SDLK_t){//se puede modificar
				if (static_cast<Jugable*>(personaje)->getEstado())
					inventarioToBaul();
			}


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
		if (evento.type == SDL_KEYUP&&evento.key.keysym.sym == SDLK_s)
			guardarJuego();
	topState()->handleEvent(evento);
	} 
	return true;
};

//Método de consulta de la variable de control 'error'.
bool Juego::getError()const {	return error;};
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
	FPSCAP = 1 / 60.0F;
	accumulator = 0;
	Uint32 delta = 0;
	float d = 0;

	float fp = FPSCAP * 1000;
	Uint32 s = 0;
	Uint32 contSeg= 0;
	int fpsCount = 0;
	int lasssst = 0;
	bool stop = false;
	cout << "PLAY \n";
	lastUpdate = SDL_GetTicks();
	contSeg = SDL_GetTicks();
	world->Step(1.0f / 60.0f, 6, 2);
	draw();
	handle_event();
	while (!exit) {
		handle_event();
		/*if (SDL_GetTicks() - lastUpdate >= MSxUpdate) {
			lastUpdate = SDL_GetTicks();
		}*/

		//delta 
		s = SDL_GetTicks();
		delta = SDL_GetTicks() - contSeg;
		contSeg = SDL_GetTicks();
		d = delta;
		accumulator += d;
		while (accumulator > fp){
			update();
			world->Step(FPSCAP, 6, 2);
			fpsCount++;
			accumulator -= fp;
		}
		if (fpsCount >= 60){
			fpsCount = 0;
		
		}
		
			draw();
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

	/*popState();
	pushState(newState);*/

	if (typeid(*newState) == typeid(Pausa)) {
		pushState(newState);
	}

	else {
		popState();
		pushState(newState);
	}
}

void Juego::pushState(EstadoJuego* newState){
	estados.push(newState);
}

void Juego::popState(){
	//Camera = new Camara(static_cast<Entidad*>(personaje[pJuego->getActivo()])->getRect(), window.ancho, window.alto);
	//juego->setCamera(Camera);
	/*delete topState();
	estados.pop();*/
	
	if (!estados.empty()) {
		delete topState();
		estados.pop();
	}

}

void Juego::popStateandCamera(){
	
	
	if (!estados.empty()) {
		delete topState();
		estados.pop();
	}
	Play *aux = static_cast<Play*>(topState());
	SDL_Rect*personajeActivo = (static_cast<Entidad*>(aux->personaje[getActivo()])->getRect());
	setPlayer(aux->personaje[getActivo()]);
	
	Camera->setTarget(personajeActivo);
}

void Juego::freeEstadoss() {

	while (!estados.empty()) {

		popState();
	}
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
	try{
		if (zonaNombre == "ZonaDesguace")
			zona = new ZonaDesguace(this);
		else if (zonaNombre == "ZonaBosque")
			zona = new ZonaBosque(this);
		else if (zonaNombre == "ZonaBase"){
			zona = new ZonaBase(this);
		}
		else if (zonaNombre == "ZonaPinApple") {
			zona = new ZonaPinApple(this);
		}
		else if (zonaNombre == "ZonaTutorial") {
			zona = new ZonaTutorial(this);
		}
	}
	catch (...){
		std::cout << "hubiera petado \n";
		setZona(zonaNombre);
	}
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

void Juego::setGameOver(){
	reproducirEfecto("Muerte");
	gameOver = true;
	//changeState(new GameOver(this));
	//Reiniciamos el inventario
	vaciaInventario();

	pushState(new GameOver(this));
}

void Juego::setFinZona(){
	pushState(new MenuFinDeZona(this));
}

void Juego::reiniciar(){
	static_cast<Jugable*>(getPlayer())->setStats();
}

void Juego::guardarJuego()
{
	ofstream kek;
	kek.open("save.kek");
	//ya ha jugado
	(firstPlay) ? kek<<0: kek<<1;
	kek << endl;
	//progreso nave
	kek << progresoNave << endl;
	//guardado baul
	kek << baul->getMap().size()<<endl;
	std::map<string,int> subbaul =baul->getMap();
	for (std::map<string, int>::iterator it = subbaul.begin(); it != subbaul.end();it++) {
		kek << it->first << " " << it->second<<endl;
	}
	
	//guardado inventario
	kek << inventario->getMap().size() << endl;
	subbaul = inventario->getMap();
	for (std::map<string, int>::iterator it = subbaul.begin(); it != subbaul.end(); it++) {
		kek << it->first << " " << it->second << endl;
	}
	
	//guardado SD
	kek << mem.size() << endl;
	for (std::map<std::string, bool>::iterator it = mem.begin(); it != mem.end(); it++) {
		kek << it->first << " " << ((it->second)?'1':'0')<< endl;
	}

	kek.close();
}

bool Juego::cargarJuego()
{
	ifstream kek;
	kek.open("save.kek");
	if (!kek.fail()) {
		int aux;
		kek >> aux;
		firstPlay = aux;
		kek >> aux;
		progresoNave = aux;
		int nLineas = 0;
		kek >> nLineas;
		for (int i = 0; i < nLineas; i++) {
			string nomObjeto;
			int cantObjeto;
			kek >> nomObjeto >> cantObjeto;
			baul->insertItem(nomObjeto, cantObjeto);

		}
		kek >> nLineas;
		for (int i = 0; i < nLineas; i++) {
			string nomObjeto;
			int cantObjeto;
			kek >> nomObjeto >> cantObjeto;
			inventario->insertItem(nomObjeto, cantObjeto);

		}

		for (int i = 0; i < nLineas; i++) {
			string nomObjeto;
			int cantObjeto;
			kek >> nomObjeto >> cantObjeto;
			mem.insert(std::pair<std::string, bool>(nomObjeto, (cantObjeto) ? true : false));

		}
		kek.close();
	}
	return true;
}

