#include "ZonaPinApple.h"



ZonaPinApple::ZonaPinApple(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon3";

	setHabitaciones(1, 1);
	setNivelActual();
	initRooms();
}


ZonaPinApple::~ZonaPinApple()
{
}
