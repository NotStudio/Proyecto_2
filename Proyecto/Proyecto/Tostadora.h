#ifndef TOSTADORA_H_
#define TOSTADORA_H_
#include "Jugable.h"

class Tostadora :
	public Jugable
{
protected:
	SDL_TimerID Disparar;
	Uint32 cadencia = 350;
	bool disparar=true;
public:
	void reactivarDisparo(){
		disparar = true;
	}
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();
	void disparo();
	void setStats();

	virtual void update();
};

#endif