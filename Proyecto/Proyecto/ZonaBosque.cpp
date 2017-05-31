#include "ZonaBosque.h"


ZonaBosque::ZonaBosque(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	id = "zon1";

	setHabitaciones(1,1);	
	setNivelActual();
	initRooms();
	
	//pJuego->getCamera()->setLimite({ pJuego->getCameraRect().x, pJuego->getCameraRect().y, pJuego->getCameraRect().w + 500, pJuego->getCameraRect().h + 500 });

}


ZonaBosque::~ZonaBosque()
{
}
