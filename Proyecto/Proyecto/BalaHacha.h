#pragma once
#include "Bala.h"
class BalaHacha : Bala
{
public:
	BalaHacha(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry);
	~BalaHacha();

	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
private:
	int rebotes = 3;
	int cont = 0;
	float dirx_;
	float diry_;
};

