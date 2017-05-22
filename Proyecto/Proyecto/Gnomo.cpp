#include "Gnomo.h"


Gnomo::Gnomo(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x, y, 96, 96}, "gnomo", 1000)
{
}


Gnomo::~Gnomo()
{
}


uint32 changeStateCB(Uint32 intervalo, void * param){
	static_cast<Gnomo*>(param)->changeState();
	return 0;
}

void Gnomo::changeState(){

}

void Gnomo::Idle(){

	if (!empezado){
		empezado = true;


		SDL_AddTimer(2000u, changeStateCB, this);
		//timers
		//El timer que se activa mas tarde es el changestate
	}
}
