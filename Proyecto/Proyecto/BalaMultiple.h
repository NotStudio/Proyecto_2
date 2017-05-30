#pragma once
#include "BalaEnemiga.h"
#include "ZonaAccion.h"

class BalaMultiple : public BalaEnemiga
{
public:
	BalaMultiple(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry);
	~BalaMultiple();

	virtual void update();
	//LTimer contador;
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);

private:
	void dividir();
	b2Vec2 origen;
	float32 distViajada;
	float distMax;
	bool choque = false;
	float aux1, aux2;
};

