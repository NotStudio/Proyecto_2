#include "ZonaPinApple.h"



ZonaPinApple::ZonaPinApple(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon3";

	setHabitaciones(30, 3);
	setNivelActual();
	initRooms();
}


ZonaPinApple::~ZonaPinApple()
{
}
