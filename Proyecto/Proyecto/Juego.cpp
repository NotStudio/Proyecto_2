#include "Juego.h"
#include "Tostadora.h"


//Constructora que inicializa todos los atributos de la clase Juego.
Juego::Juego(b2World* mundo) : error(false), gameOver(false), exit(false), score(0), world(mundo)
{
	window.alto = 600; //Tamaño de la ventana.
	window.ancho = 800;
	fondoRect.x = 0; //Posición y tamaño de la ventana.
	fondoRect.y = 0;
	fondoRect.w = window.ancho;
	fondoRect.h = window.alto;
	mousePos.x = 0;//Posición del raton, inicialización trivial.
	mousePos.y = 0;
	//iniciazión de SDL
	if (!initSDL()) {
		error = true;
		std::cout << "Ha ocurrido un error con SDL";
	}
	//Esto es el wall de mexico los estados hundidos
	r.x = 100;
	r.y = 100;
	r.h = 50;
	r.w = 50;
	
	//Añadimos al vector del nombre de las texturas los nombres de las imágenes. Tienen que tener un orden concreto.
	nombreTexturas.emplace_back("../Material/Tostadora_idle.png");
	nombreTexturas.emplace_back("../Material/Gato_idle.png");
	nombreTexturas.emplace_back("../Material/Wall_idle.png");
	nombreTexturas.emplace_back("../Material/Background_idle.jpg");
	
	world->SetContactListener(&listener);
	
	b2BodyDef tostBodydef;
	tostBodydef.type = b2_dynamicBody;
	tostBodydef.position.Set(50.0f, 50.0f);

	b2Body* tostBody = world->CreateBody(&tostBodydef);

	b2PolygonShape tostBox;
	tostBox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef fDef;
	fDef.shape = &tostBox;
	fDef.density = 1.0f;
	fDef.friction = 1.0f;
	tostBody->CreateFixture(&fDef);
	tostadora = tostBody;
	

	b2BodyDef wallBodydef;
	wallBodydef.type = b2_staticBody;
	wallBodydef.position.Set(400.0f, 400.0f);

	b2Body* wallBody = world->CreateBody(&wallBodydef);

	b2PolygonShape wallbox;
	wallbox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef wDef;
	wDef.shape = &wallbox;
	wallBody->CreateFixture(&wDef);
	wall= wallBody; 
	recta.h = 50;// tamaño de la imagen
	recta.w = 50;
	


	b2BodyDef gBodydef;
	gBodydef.type = b2_dynamicBody;
	gBodydef.position.Set(150.0f, 100.0f);

	b2Body* gBody = world->CreateBody(&gBodydef);

	b2PolygonShape gBox;
	gBox.SetAsBox(25.0f, 25.0f);
	


	b2FixtureDef gDef;
	gDef.shape = &gBox;
	gDef.density = 50000.0f;
	gDef.friction = 1.0f;
	gBody->CreateFixture(&gDef);
	gato = gBody;
	r2.h = 100;
	r2.w = 100;


	for (int i = 0; i < 322; i++) { // init them all to false
		KEYS[i] = false;
	}
	
	//Arrancamos las texturas y los objetos.
	initMedia();
	objetos.push_back(tostadora);
	objetos.push_back(gato);
	objetos.push_back(wall);
	toasty = new Tostadora(this, r);
	run();	
	
}

Juego::~Juego()
{

	//Liberamos los objetos.
	freeMedia();
	
	//Liberamos SDL.
	closeSDL();
	pWindow = nullptr;
	pRenderer = nullptr;

	//Liberar cosas de la Física
	
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
		/*
		mapTexturas.emplace(std::make_pair(entity, std::make_pair(anim, new TexturasSDL)));
		mapTexturas.at(entity).second->load(pRenderer,aux);*/
		
		try{
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

	b2Vec2 point;
	world->Step(1.0f/60.0f, 6, 2);
	toasty->update();
	
	
	//std::cout << point.x << " " << point.y << "\n";
}

void Juego::draw(){
	
	SDL_RenderClear(pRenderer);
	mapTexturas.at("Background").at("idle")->draw(pRenderer, fondoRect, &fondoRect);
	toasty->draw();
	unordered_map<string, unordered_map<string, TexturasSDL*>>::iterator it = mapTexturas.begin();
	b2Vec2 posT;
	int i = 0;
	while (it != mapTexturas.end()){
		mapTexturas.at(it->first).at("idle")->draw(pRenderer, r, nullptr);
		it++;
		i++;
	}
	

	SDL_RenderPresent(pRenderer);

}


void Juego::run() {

	if (!error) {
		cout << "PLAY \n";
		lastUpdate = SDL_GetTicks();
		handle_event();
		while (!exit) {
			update();
			lastUpdate = SDL_GetTicks();
			draw();
			handle_event();
		}
		if (exit) cout << "EXIT \n";
		else if (gameOver) {
			cout << "GAME OVER \n";
		}
	}
};

bool Juego::inputQuery(int numButton) {
	return KEYS[numButton];
}

b2World* Juego::getWorld() {
	return world;
}