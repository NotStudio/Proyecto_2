#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon2";
	//getRoomIni()
	for (size_t i = 0; i < 3; i++)
	{
		niveles->push_back(new Room(pJuego, niveles, this));
	}
	//GetRoomBoss(this)
	setRect();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
