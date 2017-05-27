#pragma once
#include "BalaEnemiga.h"

class BalaHacha : public BalaEnemiga
{
public:
	BalaHacha(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry);
	~BalaHacha();

	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);

	void bounce(b2Body* tileBody);// Rebote del hacha;
private:
	int rebotes = 3;
	int numRebotes = 0;
	float dirx_ = 0;
	float diry_ = 0;
};

