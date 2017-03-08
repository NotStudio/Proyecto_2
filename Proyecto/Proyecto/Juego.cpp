#include "Juego.h"
#include "Tostadora.h"
#include "Camara.h"
#include "ZonaAccion.h"
#include "Play.h"


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
	r.x = 100;
	r.y = 100;
	r.h = 64;
	r.w = 64;
	
	//Añadimos al vector del nombre de las texturas los nombres de las imágenes. Tienen que tener un orden concreto.
	
	nombreTexturas.emplace_back("../Material/Tostadora_idle.png");
	nombreTexturas.emplace_back("../Material/Gato_idle.png");
	nombreTexturas.emplace_back("../Material/Wall_idle.png");
	nombreTexturas.emplace_back("../Material/Background_idle.jpg");
	nombreTexturas.emplace_back("../Material/Bala_idle.png");
	nombreTexturas.emplace_back("../Material/tilesheet_test.png");
	
	world->SetContactListener(&listener);
	

	for (int i = 0; i < 322; i++) { // init them all to false
		KEYS[i] = false;
	}
	
	//Arrancamos las texturas y los objetos.
	initMedia();
	personaje = new Tostadora(this,r);
	Camera =new Camara(static_cast<Entidad*>(personaje)->getRect(), window.ancho, window.alto);
	int w = 50;
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
	//borrar zona
	delete zona;
	
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
		entity = nombreTexturas[i].erase(0, 12);
		entity.erase(entity.end()-4,entity.end());

		anim = entity.substr(entity.size() - 4, 4);
		entity.erase(entity.end() - 5, entity.end());
		
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
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
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
//Método que controla los eventos.
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
bool Juego::getError() {

	return error;

};

void Juego::salir() {

		exit = true;
	
}



void Juego::update(){

	topState()->update();
	Camera->update();
	Camera->setLimite(zona->getNivelActual());
}

void Juego::draw(){
	
	SDL_RenderClear(pRenderer);
	topState()->draw();
	SDL_RenderPresent(pRenderer);

}


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
		if (contSeg >= lasssst + 1000) {
			std::cout << fpsCount << " ";
			fpsCount = 0;
			lasssst = contSeg;
			contSeg = 0;
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



bool Juego::inputQuery(int numButton) {
	return KEYS[numButton];
}

b2World* Juego::getWorld() {
	return world;
}

void Juego::setZona(ZonaJuego* nwZona) {
	//borrar la zona anterior.
	zona = nwZona;

}