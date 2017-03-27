#include "ZonaJuego.h"



ZonaJuego::ZonaJuego(Juego* punteroJuego):pJuego(punteroJuego)
{
	punteroJuego->setZona(this);
}


ZonaJuego::~ZonaJuego()
{
	
	nivelActual = nullptr;
}

void ZonaJuego::draw() {

	nivelActual->render();
}

SDL_Rect ZonaJuego::getNivelActual() {

	return nivelActual->getArea();
}

void ZonaJuego::update() {
	nivelActual->update();
}
