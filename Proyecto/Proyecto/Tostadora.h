#ifndef TOSTADORA_H_
#define TOSTADORA_H_
#include "Jugable.h"
class Tostadora :
	public Jugable
{
protected:
	SDL_TimerCallback akak(Uint32 intervalo, void * param){
		
		return SDL_TimerCallback(intervalo);
	}
	Uint32 contador = 0;
	SDL_TimerID Disparar;
	uint32 cadencia = 500;
	bool disparar=true;
public:
	void reactivarDisparo(){
		disparar = true;
	}
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();

	virtual void onColisionEnter(Objeto* contactObject);
	void disparo();

	virtual void update();
};

#endif