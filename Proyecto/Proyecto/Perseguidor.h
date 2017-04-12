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
	Perseguidor(Juego* punteroJuego, int,int);
	~Perseguidor();
	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* obj, b2Body* b1, b2Body* b2);
	virtual void dropItems();
	virtual void comportamiento();
	virtual void tellBody(b2Body* b);
	b2Body* b2;
private:
	float coefMov;
	
	
};

#endif