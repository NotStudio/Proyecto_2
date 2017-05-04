#include "ZonaJuego.h"



ZonaJuego::ZonaJuego(Juego* punteroJuego):pJuego(punteroJuego)
{
	
}


ZonaJuego::~ZonaJuego()
{
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
