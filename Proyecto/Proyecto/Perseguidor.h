#pragma once
#ifndef PERSEGUIDOR_H_
#define PERSEGUIDOR_H_
#ifndef Enemigo_h_
#define Enemigo_h_
#endif



#include "Jugable.h"
#include "Enemigo.h"
class Perseguidor :
	public Enemigo
{
public:
	Perseguidor(Juego* punteroJuego, SDL_Rect entrada);
	~Perseguidor();
	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject);
	virtual void dropItems();
	virtual void comportamiento();
private:
	float coefMov;
	
	
};

#endif