#ifndef ZONA_BASE_H_
#define ZONA_BASE_H_

#include "ZonaJuego.h"
class ZonaBase :
	public ZonaJuego
{
public:
	ZonaBase(Juego* punteroJuego);
	virtual ~ZonaBase();
	virtual void draw();
	virtual void update();
	virtual SDL_Rect getNivelActual();
};

#endif