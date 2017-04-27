#pragma once
#include "Enemigo.h"
class Sierra :
	public Enemigo
{
public: //dir 0=horizontal, 1= vertical
	Sierra(Juego* punteroJuego, int,int, int dir);
	~Sierra();

	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void comportamiento();

private:
	
	int direccion;

	bool col;
};

