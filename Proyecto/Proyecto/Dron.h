#ifndef DRON_H
#define DRON_H
#include "Enemigo.h"
class Dron :
	public Enemigo
{
	int dirX, dirY;
	b2Vec2 vel;

	void rebote(b2Body* tile);
	void hit(int dmg);
	void spawnBalas();
	bool doDieAction;

public:
	Dron(Juego* punteroJuego, int, int);
	virtual ~Dron();

	virtual void move();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void muerte();
	virtual void comportamiento();
	virtual void desactivar();

};
#endif DRON_H
