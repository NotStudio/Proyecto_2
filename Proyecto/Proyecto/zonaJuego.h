#ifndef ZONA_JUEGO_H_
#define ZONA_JUEGO_H_

class ZonaJuego
{
public:

	ZonaJuego()
	{
	}

	virtual ~ZonaJuego()
	{
	}

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual SDL_Rect getNivelActual() = 0;

};

#endif