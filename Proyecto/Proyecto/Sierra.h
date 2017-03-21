#pragma once
#include "Enemigo.h"
class Sierra :
	public Enemigo
{
public: //dir 0=horizontal, 1= vertical
	Sierra(Juego* punteroJuego, SDL_Rect a, int dir);
	~Sierra();

	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject = nullptr);

private:
	
	int direccion;

	bool col;
};

