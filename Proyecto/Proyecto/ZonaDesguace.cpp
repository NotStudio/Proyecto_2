#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon2";
	setHabitaciones(10,3);
	initRooms();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
