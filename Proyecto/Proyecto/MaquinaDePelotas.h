#pragma once
#include "Enemigo.h"
class MaquinaDePelotas :
	public Enemigo
{
	int cadencia = 1000;
	Uint32 contador = 0;
public:
	MaquinaDePelotas(Juego* punteroJuego, SDL_Rect entrada);
	~MaquinaDePelotas();
	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject);
};

