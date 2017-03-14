#ifndef TOSTADORA_H_
#define TOSTADORA_H_
#include "Jugable.h"
class Tostadora :
	public Jugable
{
protected:
	SDL_TimerID Disparar;
	Uint32 cadencia = 500;
	bool disparar=true;
public:
	void reactivarDisparo(){
		disparar = true;
	}
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();
	void disparo();

	virtual void update();
};

#endif