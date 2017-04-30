#pragma once
#include "HUDbase.h"
#include "Juego.h"
class HUDinventory :
	public HUDbase
{
public:
	HUDinventory(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim);
	virtual ~HUDinventory();

	void draw();

	SDL_Rect * getRect() {
		return sprite;
	}
	

	bool getInvState(){
	
		return mostrar;
	};


private:

	Juego* pjuego;

	Juego::Animacion animacion;

	SDL_Rect* sprite;
	SDL_Rect obj;
	SDL_Rect obj1;
	SDL_Rect obj2;
	SDL_Rect obj3;

	string id;

	string anim;

	bool mostrar = false;
};

