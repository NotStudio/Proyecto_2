#pragma once
#include "Bala.h"
#include "LTimer.h"
#include "Jugable.h"
enum fase { viajando = 0, parada };
class BalaAceite :
	public Bala
{
public:
	BalaAceite(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry);
	~BalaAceite();
	virtual void update();
	void grow();
	LTimer contador;
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
private:
	void changePhase();
	float32 tiempoCharco;
	b2Vec2 origen;
	float32 distViajada;
	fase faseact;
	float distMax;
	bool choque = false;

};

