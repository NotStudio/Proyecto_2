
#ifndef HUD_H_
#define HUD_H_
#include "HUDbase.h"
#include "Juego.h"
#include "HUDImage.h"
#include "HUDText.h"
class HUD : public HUDbase
{
public:
	HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim);
	virtual ~HUD();

	void updateHUD();
	void draw();

	SDL_Rect * getRect() {
		return sprite;
	}


	//void setInventario(bool state);

private:

	SDL_Rect fondoVida;
	HUDImage * vida;
	Juego* pjuego;

	Juego::Animacion animacion;

	SDL_Rect* sprite;

	string id;

	string anim;

	HUDImage * velMov;
	HUDImage * ataque;
	HUDImage * velAtaq;

	HUDText *statVelMov;
	HUDText *statDanyo;
	HUDText *statVelAtaq;
	HUDText *VidaGui;


	HUDImage * marcoStats;
	HUDImage * cables;
	int alto, ancho;
	int maxVidas;
	int vidasAct;
	float medAlto, medAncho;
	//bool mostrar = true;
};

#endif 

