#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon2";

	setHabitaciones(25, 4);
	initRooms();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
