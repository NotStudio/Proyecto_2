#ifndef PLAY_H_
#define PLAY_H_

#include "EstadoPG.h"
#include "Zona.h"
//#include "Inventory.h"
class Play :
	public EstadoPG
{
public:
	Play(Juego * juego);
	virtual ~Play();

	virtual void draw();

	virtual void update();

	static void setZona();

	void setCamera(SDL_Rect *target){
		Camera->setTarget(target);
	}

	enum state {JUGANDO, CARGANDO};

	static state estado;

	void setState(state s) {
		estado = s;
	}
	vector<Objeto*> personaje;

private:
	
	std::vector<Objeto*> enemigos;
	
	HUDbase* vidasHUD;

	HUDbase* inventory;

	Camara *Camera;

	Zona* zona;

	Inventory* inventario;//inventario en las rooms

	Inventory* baul;//baul de la base

	std::map<std::string, bool> memorias;

	static bool needGetZona;

	static bool needCarga;

};

#endif