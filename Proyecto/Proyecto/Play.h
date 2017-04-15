#ifndef PLAY_H_
#define PLAY_H_

#include "EstadoPG.h"
#include "Zona.h"
class Play :
	public EstadoPG
{
public:
	Play(Juego * juego);
	virtual ~Play();

	virtual void draw();

	virtual void update();

	static void setZona();

	enum state {JUGANDO, CARGANDO};

	static state estado;

	void setState(state s) {
		estado = s;
	}
	

private:
	
	vector<Objeto*> personaje;
	

	std::vector<Objeto*> enemigos;
	
	HUDbase* vidasHUD;

	Camara *Camera;

	Zona* zona;

	static bool needGetZona;

	static bool needCarga;

};

#endif