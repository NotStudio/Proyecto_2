#ifndef ZONA_H_
#define ZONA_H_
#include <SDL.h>
class Zona //Clase interfaz
{
public:

	Zona()
	{
	}

	virtual ~Zona()
	{
	}

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual SDL_Rect getNivelActual() = 0;

};

#endif