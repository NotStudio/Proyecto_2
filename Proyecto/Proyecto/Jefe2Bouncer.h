#pragma once
#include "Enemigo.h"
class Jefe2Bouncer :
	public Enemigo
{
	int dirX, dirY;
	b2Vec2 vel;
	int level;
	bool doDivision;
	void spawnSons();
	bool tarjetaSpawned;

public:
	Jefe2Bouncer(Juego* punteroJuego, int x, int y, int lvl);
	virtual ~Jefe2Bouncer();

	void bounce(b2Body* tileBody);
	virtual void move();
	virtual void comportamiento();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void dropItems();
	virtual void muerte();
	virtual void desactivar();
};

