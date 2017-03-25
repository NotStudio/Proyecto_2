#include "ZonaBase.h"
#include "Juego.h"
#include "Room.h"


ZonaBase::ZonaBase(Juego* punteroJuego):ZonaJuego(punteroJuego)
{
	niveles->push_back(new Room(pJuego, niveles));
	nivelActual = niveles->at(0);
}


ZonaBase::~ZonaBase()
{
}

 SDL_Rect ZonaBase::getNivelActual() {

	 return nivelActual->getArea();
};
 
 void ZonaBase::draw() {
	 ZonaJuego::draw();
 };

 void ZonaBase::update() {};