#pragma once
#include "Jugable.h"
class Cambiante :
	public Jugable
{
public:
	Cambiante(Juego* punteroJuego, SDL_Rect spritePar);
	virtual~Cambiante();

	void reactivarDisparo(){
		disparar = true;
	}

protected:
	SDL_TimerID Disparar;
	Uint32 cadencia = 350;
	bool disparar = true;

	void disparo();
	void ataqueMele();
	void forma(bool mele);

	virtual void update();

	void cambio();

	float furia = 1.0f;

	bool mele = false;

	
};

