#pragma once
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

