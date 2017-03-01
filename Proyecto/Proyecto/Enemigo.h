#pragma once
#include "NPC.h"
class Enemigo : public NPC
{
public:
	Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~Enemigo();
	virtual void move();
	void virtual onColisionEnter(Objeto* contactObject);
	void virtual update();
};

