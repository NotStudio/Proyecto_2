#include "ZonaBosque.h"


ZonaBosque::ZonaBosque(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon1";

	setHabitaciones(1,1);	initRooms();
	setNivelActual();
	
	//pJuego->getCamera()->setLimite({ pJuego->getCameraRect().x, pJuego->getCameraRect().y, pJuego->getCameraRect().w + 500, pJuego->getCameraRect().h + 500 });

}


ZonaBosque::~ZonaBosque()
{
}
