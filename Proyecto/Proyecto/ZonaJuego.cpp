#include "ZonaJuego.h"



ZonaJuego::ZonaJuego(Juego* punteroJuego):pJuego(punteroJuego)
{
	punteroJuego->setZona(this);
}


ZonaJuego::~ZonaJuego()
{
	for (size_t i = 0; i < niveles->size(); i++)
	{
		delete niveles->at(i);
		niveles->at(i) = nullptr;
	}
	delete niveles;
	niveles = nullptr;
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
