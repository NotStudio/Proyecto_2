#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon2";
	setHabitaciones(1,1);
	initRooms();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
