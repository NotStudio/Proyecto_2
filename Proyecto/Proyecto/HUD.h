
#ifndef HUD_H_
#define HUD_H_
#include "HUDbase.h"
#include "Juego.h"
class HUD: public HUDbase
{
public:
	HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim);
	~HUD();


	void draw();
	
	SDL_Rect * getRect() {
		return sprite;
	}

private:

	Juego* pjuego;

	Juego::Animacion animacion;

	SDL_Rect* sprite;

	string id;

	string anim;
};

#endif 

