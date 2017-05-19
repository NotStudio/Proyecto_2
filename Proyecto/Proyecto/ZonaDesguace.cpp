#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon2";

	setHabitaciones(1,1);
	initRooms();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
