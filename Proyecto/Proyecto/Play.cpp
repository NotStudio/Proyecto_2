#include "Play.h"
#include "checkML.h"
#include "ZonaBase.h"
#include "ZonaAccion.h"
#include "Tostadora.h"
#include "Camara.h"
#include "HUD.h"

Uint32 callbackCarga(Uint32 param, void *p);
bool Play::needGetZona = false;
bool Play::needCarga = true;
Play::state Play::estado = Play::CARGANDO;

Play::Play(Juego * juego) : EstadoPG(juego)
{
	personaje = new Tostadora(juego, SDL_Rect{ 576,75,64,64 });
	juego->setPlayer(personaje);
	Juego::Ventana window = juego->getWindow();
	Camera = new Camara(static_cast<Entidad*>(personaje)->getRect(), window.ancho, window.alto);
	juego->setCamera(Camera);
	juego->setZona("");
	vidasHUD = new HUD(juego, SDL_Rect{ 20,0,34,55 }, "Battery4", "idle");

}


Play::~Play()
{
	delete vidasHUD;
	vidasHUD = nullptr;
	delete Camera;
	Camera = nullptr;
	delete personaje;
	//borrar zona
	delete zona;
}

void Play::draw(){
	if (estado == CARGANDO) {
		zona = pJuego->getZona();
		pJuego->getTextura("Loading", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0,0,800,600 }, nullptr);

	}
	else {
		zona->draw();
		personaje->draw();
		vidasHUD->draw();
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
		personaje->update();
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
