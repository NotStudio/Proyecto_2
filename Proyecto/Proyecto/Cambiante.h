#pragma once
#include "Jugable.h"
class Cambiante :
	public Jugable
{
public:
	Cambiante(Juego* punteroJuego, SDL_Rect spritePar);
	virtual~Cambiante();

	void reactivarDisparo(){
		disparar = true;
	}


protected:
	SDL_TimerID Disparar;
	Uint32 cadencia = 350;
	bool disparar = true;

	void disparo();
	void ataqueMele();
	void forma(bool mele);
	void cambio();

	virtual void update();


	bool mele = false;
	float furia = 1.0f;


	b2Shape* st;

	b2BodyDef bdt;
	b2Body* bt;
	b2FixtureDef fdt;

};

