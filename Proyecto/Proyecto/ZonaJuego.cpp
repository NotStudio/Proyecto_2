#include "ZonaJuego.h"



ZonaJuego::ZonaJuego(Juego* punteroJuego):pJuego(punteroJuego)
{
	
}

void ZonaJuego::initRooms()
{
	for (auto n : *niveles) {
		n->InitRoom();
		n->abrirPuertas();
	}
}


ZonaJuego::~ZonaJuego()
{
}

void ZonaJuego::draw() {

	nivelActual->render();
}

SDL_Rect ZonaJuego::getNivelActual() {

	return *nivelActual->getArea();
}

void ZonaJuego::update() {
	nivelActual->update();
}
