#ifndef ESTADO_JUEGO_H_
#define ESTADO_JUEGO_H_
#include <SDL_events.h>

class EstadoJuego
{
public:

	EstadoJuego()
	{
	}

	virtual ~EstadoJuego()
	{
	}
	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif