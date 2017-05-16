
#ifndef HUD_H_
#define HUD_H_
#include "HUDbase.h"
#include "Juego.h"
#include "HUDImage.h"
#include "HUDText.h"
class HUD: public HUDbase
{
public:
	HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim);
	virtual ~HUD();


	void draw();
	
	SDL_Rect * getRect() {
		return sprite;
	}

	void updateHUD();

	//void setInventario(bool state);

private:

	Juego* pjuego;

	Juego::Animacion animacion;

	SDL_Rect* sprite;

	string id;

	string anim;

	HUDImage kek;

	HUDText kruk;

	HUDImage vida; 

	HUDText statAtaque;

	HUDText statVelmov;

	HUDText statvelAtaque;


	//bool mostrar = true;
};

#endif 

