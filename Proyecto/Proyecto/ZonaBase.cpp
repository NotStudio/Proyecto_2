#include "ZonaBase.h"
#include "Juego.h"
#include "Room.h"


ZonaBase::ZonaBase(Juego* punteroJuego):ZonaJuego(punteroJuego)
{
	id = "zon1";
	baseNivel = new Room(pJuego, this, pJuego->getBaseRoom(), {0,0});
	nivelActual = baseNivel;
	pJuego->getCamera()->setLimite(nivelActual->getArea());
	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::BASE);
	static_cast<Jugable*>(pJuego->getPlayer())->setPos(200,50);
	baseNivel->InitRoom();
}


ZonaBase::~ZonaBase()
{
	delete baseNivel;
	baseNivel = nullptr;
}

 SDL_Rect ZonaBase::getNivelActual() {

	 return nivelActual->getArea();
};
 
 void ZonaBase::draw() {
	 ZonaJuego::draw();
 };

 void ZonaBase::update() {};