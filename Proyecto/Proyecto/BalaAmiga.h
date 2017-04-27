#pragma once
#include "Bala.h"
class BalaAmiga :
	public Bala
{
public:
	BalaAmiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry, int danyo);
	int getDanyo() { return danyo; }
	~BalaAmiga();
private:
	int danyo;

};

