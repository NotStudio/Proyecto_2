#ifndef TOSTADORA_H_
#define TOSTADORA_H_
#include "Jugable.h"
class Tostadora :
	public Jugable
{
public:
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();

	virtual void onColisionEnter(Objeto* contactObject);
};

#endif