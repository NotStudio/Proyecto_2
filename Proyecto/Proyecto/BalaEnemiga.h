#pragma once
#include "Bala.h"
class BalaEnemiga :
	public Bala
{
public:
	BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry);
	BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, string objectId,float32 vel, float32 dirx, float32 diry);
	
	~BalaEnemiga();
};

