#pragma once
#include "Enemigo.h"
class MaquinaDePelotas :
	public Enemigo
{
	int cadencia = 1000;
	Uint32 contador = 0;
public:
	MaquinaDePelotas(Juego* punteroJuego, int,int);
	~MaquinaDePelotas();
	void ataque();
	virtual void comportamiento();
	void virtual onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
};

