#include "Play.h"
#include "checkML.h"
#include "ZonaBase.h"
#include "ZonaAccion.h"
#include "Tostadora.h"
#include "Camara.h"
#include "HUD.h"
#include "Cambiante.h"
#include "PjDañoArea.h"
#include "HUDinventory.h"

Uint32 callbackCarga(Uint32 param, void *p);
bool Play::needGetZona = false;
bool Play::needCarga = true;
Play::state Play::estado = Play::CARGANDO;

Play::Play(Juego * juego) : EstadoPG(juego)
{

	
	personaje.push_back( new Tostadora(juego, SDL_Rect{ 576, 75, 64, 64 }));
	juego->NewPersonaje();
	personaje.push_back( new Cambiante(juego, SDL_Rect{ 576, 75, 64, 64 }));
	juego->NewPersonaje();
	personaje.push_back(new PjDañoArea(juego, SDL_Rect{ 576, 75, 64, 64 }));
	juego->NewPersonaje();
	juego->setPlayer(personaje[pJuego->getActivo()]);
	Juego::Ventana window = juego->getWindow();
	Camera = new Camara(static_cast<Entidad*>(personaje[pJuego->getActivo()])->getRect(), window.ancho, window.alto);
	juego->setCamera(Camera);
	juego->setZona("ZonaBase");
	vidasHUD = new HUD(juego, SDL_Rect{ 20,0,34,55 }, "Battery4", "idle");
	inventory = new HUDinventory(juego, SDL_Rect{ 150, 500, 500, 100 }, "Inventory", "idle");
	//SDL_Rect{ (WINwidth/2) - width/2, WINheight - height , ... , ...}
	
	inventario = new Inventory();
	juego->setInventory(inventario);
	/*inventario->insertItem("Fusible", 2);
	inventario->insertItem("Engranaje", 2);
	inventario->insertItem("Chip", 2);*/
	//inventario->insertItem("Madera", 2);

	baul = new Inventory();
	juego->setBaul(baul);

}


Play::~Play()
{
	delete vidasHUD;
	vidasHUD = nullptr;
	delete Camera;
	Camera = nullptr;
	for (int i = 0; i < personaje.size(); i++){
		delete personaje[i];
		personaje[i] = nullptr;
	}
	//borrar zona
	delete zona;
	delete baul;
	baul = nullptr;
	delete inventario;
	inventario = nullptr;
	delete inventory;
	inventory = nullptr;
	zona = nullptr;
}

void Play::draw(){
	if (estado == CARGANDO) {
		zona = pJuego->getZona();
		pJuego->getTextura("Loading", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0,0,800,600 }, nullptr);

	}
	else {
		zona->draw();
		personaje[pJuego->getActivo()]->draw();
		vidasHUD->draw();//hacer vector de HUDbase......................
		
		if(pJuego->getMostrar()) inventory->draw();
	}
}

void Play::update(){
	if (estado == CARGANDO) {
		if (needGetZona) { 
			zona = pJuego->getZona(); needGetZona = false; };
		if (needCarga) {
			SDL_AddTimer(1000u, callbackCarga, this);
			needCarga = false;
		}

	}
	else {
		Camera->update();
		Camera->setLimite(zona->getNivelActual());
		zona->update();
		personaje[pJuego->getActivo()]->update();
		pJuego->setInventory(inventario);
	}
	if (static_cast<Jugable*>(pJuego->getPlayer())->getStats()->vida <= 0)
	{
		//pJuego->setGameOver();	
	}

}

Uint32 callbackCarga(Uint32 param, void *p) {
	static_cast<Play*>(p)->setState(Play::JUGANDO);
		return 0;


}

void Play::setZona() {
	estado = Play::CARGANDO;
	needGetZona = true;
	needCarga = true;
}

