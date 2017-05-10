#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon2";

	setHabitaciones(9,4);
	for (size_t i = 0; i < niveles->size(); i++)
	{
		niveles->at(i)->InitRoom();
		niveles->at(i)->abrirPuertas();
	}
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
