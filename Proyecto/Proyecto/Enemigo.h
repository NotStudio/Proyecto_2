#ifndef ENEMIGO_H_
#define ENEMIGO_H_
#include "ZonaAccion.h"

#include "NPC.h"
class Enemigo : public NPC
{
protected:

	int _distancia;

	bool needDrop;
	bool isDead;
	virtual void muerte();
	virtual void comportamiento() {};
public:
	Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia);
	~Enemigo();
	void virtual onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	void virtual update();
	void draw();
	void stop();
	bool distancia();
	virtual void dropItems();
	void desactivar();
	
};
#endif
