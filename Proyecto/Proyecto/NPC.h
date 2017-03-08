#pragma once
#include "Personaje.h"
class NPC :
	public Personaje
{
public:
	NPC(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~NPC();

};

