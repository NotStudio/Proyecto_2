#include "ZonaBosque.h"


ZonaBosque::ZonaBosque(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon1";

	setHabitaciones(5, 5);
	for (size_t i = 0; i < niveles->size(); i++)
	{
		niveles->at(i)->InitRoom();
		niveles->at(i)->abrirPuertas();
	}
	setNivelActual();
	
	//pJuego->getCamera()->setLimite({ pJuego->getCameraRect().x, pJuego->getCameraRect().y, pJuego->getCameraRect().w + 500, pJuego->getCameraRect().h + 500 });

}


ZonaBosque::~ZonaBosque()
{
}
