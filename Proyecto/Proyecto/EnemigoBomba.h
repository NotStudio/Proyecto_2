#pragma once
#include "Enemigo.h"


class EnemigoBomba : public Enemigo
{
public:
	EnemigoBomba(Juego* punteroJuego, int,int);
	~EnemigoBomba();

	virtual void move();
	virtual void update();
	virtual void onColisionEnter(Objeto* contactObject=nullptr);
	void muerte();
	

private:
	
	atributos enemyStats;

	void crecer();

	float jugx;
	float jugy;
	SDL_Rect* x;
	bool visible;
};

