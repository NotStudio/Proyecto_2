#ifndef TOSTADORA_H_
#define TOSTADORA_H_
#include "Jugable.h"
class Tostadora :
	public Jugable
{
	Uint32 contador = 0;
	int cadencia = 150; // mas es igual a mas lento
public:
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();

	virtual void onColisionEnter(Objeto* contactObject);
	void disparo();

	virtual void update();
};

#endif