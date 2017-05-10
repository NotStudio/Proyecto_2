#include "ZonaBosque.h"


ZonaBosque::ZonaBosque(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon1";

	setHabitaciones(1, 1);
	for (size_t i = 0; i < niveles->size(); i++)
	{
		niveles->at(i)->InitRoom();
		niveles->at(i)->abrirPuertas();
	}
	setNivelActual();

}


ZonaBosque::~ZonaBosque()
{
}
