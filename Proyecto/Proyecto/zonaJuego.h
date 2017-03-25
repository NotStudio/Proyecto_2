#ifndef ZONA_JUEGO_H_
#define ZONA_JUEGO_H_
#include "Zona.h"
#include "Juego.h"
#include "Room.h"
class ZonaJuego :
	public Zona
{
protected:
	Juego* pJuego;
	//Vector de habitaciones/niveles
	vector<Room*>* niveles;
	//Puntero al nivel actual
	Room* nivelActual;
public:
	ZonaJuego(Juego* punteroJuego);
	virtual ~ZonaJuego();
	virtual void draw();
	virtual void update();
	virtual SDL_Rect getNivelActual();
};

#endif