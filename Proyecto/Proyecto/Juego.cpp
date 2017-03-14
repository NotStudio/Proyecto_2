#include "Juego.h"
#include "Tostadora.h"
#include "Camara.h"
#include "ZonaAccion.h"
#include "Play.h"
#include "checkML.h"
#include "HUD.h"

//Constructora que inicializa todos los atributos de la clase Juego.
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
	nombreTexturas.emplace_back("../Material/Tostadora_idle.png");
	nombreTexturas.emplace_back("../Material/Tostadora_walk.png");
	nombreTexturas.emplace_back("../Material/Tostadora_atqu.png");
	//Gato
	nombreTexturas.emplace_back("../Material/Gato_idle.png");
	//Bomba
	nombreTexturas.emplace_back("../Material/Bomba_idle.png");
	//Ladron
	nombreTexturas.emplace_back("../Material/Ladron_idle.png");

	nombreTexturas.emplace_back("../Material/Wall_idle.png");
	nombreTexturas.emplace_back("../Material/Background_idle.jpg");
	nombreTexturas.emplace_back("../Material/Bala_idle.png");
	nombreTexturas.emplace_back("../Material/tilesheet_test.png");
	nombreTexturas.emplace_back("../Material/tilesheet_zon1.png");
	nombreTexturas.emplace_back("../Material/agujero_idle.png");
	//Esto no es así.
	nombreTexturas.emplace_back("../Material/Battery4_idle.png");
	nombreTexturas.emplace_back("../Material/Battery3_idle.png");
	nombreTexturas.emplace_back("../Material/Battery2_idle.png");
	nombreTexturas.emplace_back("../Material/Battery1_idle.png");
	
	world->SetContactListener(&listener);
	

	for (int i = 0; i < 322; i++) { // init them all to false
		KEYS[i] = false;
	}

	//Arrancamos las texturas y los objetos.
	initMedia();
	personaje = new Tostadora(this, SDL_Rect{500,500,64,64});
	Camera =new Camara(static_cast<Entidad*>(personaje)->getRect(), window.ancho, window.alto);
	vidasHUD = new HUD(this, SDL_Rect{20,0,20 * 1.7,35 * 1.7 }, "Battery4", "idle");
	zona = new ZonaAccion(this);
	pushState(new Play(this));
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
	delete Camera;
	Camera = nullptr;
	delete personaje;
	//borrar zona
	delete zona;
	delete vidasHUD;
	vidasHUD = nullptr;
	
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

};
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
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("GLOBOS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.ancho, window.alto, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(pRenderer, 100, 126, 97, 255); //Set background color to black 
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

	SDL_Quit();
};

//Método que maneja el array de botones, y los activa y desactiva segun el input.
bool Juego::handle_event() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		
		switch (event.type) {

		case SDL_QUIT:
			salir(); 
			break;
		case SDL_KEYDOWN:
			KEYS[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			KEYS[event.key.keysym.scancode] = false;
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
	Camera->update();
	Camera->setLimite(zona->getNivelActual());
}
//Draw del juego, llama al dibujar del estado y del HUD
void Juego::draw(){
	
	SDL_RenderClear(pRenderer);
	topState()->draw();
	vidasHUD->draw(personaje);
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
		if (SDL_GetTicks() - lastUpdate >= MSxUpdate) {
			update();
			lastUpdate = SDL_GetTicks();
			fpsCount++;
		}
		world->Step(1.0f / 60.0f, 6, 2);
		draw();
		handle_event();
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
	return KEYS[numButton];
}

//Retornamos el mundo físico
b2World* Juego::getWorld() {
	return world;
}

//Metodo que controla el cambio de zona (zonaJugable-Base)
void Juego::setZona(ZonaJuego* nwZona) {
	//borrar la zona anterior.
	zona = nwZona;

}