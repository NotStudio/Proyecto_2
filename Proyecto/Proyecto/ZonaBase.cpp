#include "ZonaBase.h"
#include "Juego.h"
#include "Room.h"


ZonaBase::ZonaBase(Juego* punteroJuego):ZonaJuego(punteroJuego)
{

	baseNivel =  new Room(pJuego, nullptr, this);
	nivelActual = baseNivel;
	pJuego->getCamera()->setLimite(nivelActual->getArea());
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