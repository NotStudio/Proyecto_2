#pragma once
#include "Juego.h"

class ZonaJuego
{
protected:
	Juego* pJuego;

public:

	ZonaJuego(Juego* punteroJuego) :pJuego(punteroJuego)
	{
	}

	virtual ~ZonaJuego()
	{
	}

	virtual void draw() = 0;

	virtual void update() = 0;
};

