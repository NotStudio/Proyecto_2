#pragma once
#include "HUDbase.h"
#include "Juego.h"
class HUDinventory :
	public HUDbase
{
public:
	HUDinventory(Juego* punteroJuego, SDL_Rect spritePar, SDL_Rect objs, string objectId, string objectAnim);
	virtual ~HUDinventory();

	void draw();

	SDL_Rect * getRect() {
		return sprite;
	}
	SDL_Rect * getRect2() {
		return obj;
	}

	bool getInvState(){
	
		return mostrar;
	};


private:

	Juego* pjuego;

	Juego::Animacion animacion;
	Juego::Animacion animacion2;

	SDL_Rect* sprite;
	SDL_Rect* obj;

	string id;

	string anim;

	bool mostrar = false;
};

