#pragma once
#include "Jugable.h"
class PjDañoArea :
	public Jugable
{
public:
	PjDañoArea(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~PjDañoArea();

	void reactivarMele(){
		atamele = true;
	}

protected:
		
	void ataqueMele();
	virtual void update();
	bool atamele = true;
	bool destroyBody = false;


	b2Shape* st;
	b2BodyDef bdt;
	b2Body* bt;
	b2FixtureDef fdt;
};

