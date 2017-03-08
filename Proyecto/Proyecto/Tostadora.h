#pragma once
#include "Jugable.h"
class Tostadora :
	public Jugable
{
	Uint32 contador = 0;
	int cadencia = 75; // mas es igual a mas lento
public:
	Tostadora(Juego* punteroJuego, SDL_Rect spritePar);
	virtual ~Tostadora();

	virtual void onColisionEnter(Objeto* contactObject = nullptr);// Esto lo ha puesto fran ni puta idea de = nullptr
	void disparo();

	virtual void update();
};

