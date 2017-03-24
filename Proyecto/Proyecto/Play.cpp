#include "Play.h"
#include "checkML.h"
#include "ZonaAccion.h"
#include "Tostadora.h"
#include "Camara.h"
#include "HUD.h"

Play::Play(Juego * juego) : EstadoPG(juego)
{
	personaje = new Tostadora(juego, SDL_Rect{ 100,75,64,64 });
	juego->setPlayer(personaje);
	Juego::Ventana window = juego->getWindow();
	Camera = new Camara(static_cast<Entidad*>(personaje)->getRect(), window.ancho, window.alto);
	juego->setCamera(Camera);
	zona = new ZonaAccion(juego);
	juego->setZona(zona);
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

	zona->draw();
	personaje->draw();
	vidasHUD->draw();
}

void Play::update(){

	Camera->update();
	Camera->setLimite(zona->getNivelActual());
	zona->update();
	personaje->update();
	

}
