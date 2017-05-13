#pragma once
#ifndef JUEGO_H
#define JUEGO_H
#include "Juego.h"
#endif

#include "HUDObjeto.h"
class HUDObj :
	public HUDObjeto
{
public:
	HUDObj();
	~HUDObj();
	bool getActive();
	void setActive(bool aux);
	SDL_Rect getPos(){ return pos; };
	void setPos(SDL_Rect k){ pos = k; };
protected:
	SDL_Rect pos;
	bool active;
	SDL_Renderer * pRend;
	Juego * pJuego;
};

