#ifndef ENEMIGO_H_
#define ENEMIGO_H_
#include "ZonaAccion.h"

#include "NPC.h"
class Enemigo : public NPC
{
protected:

	int _distancia;

	bool needDrop;
public:
	Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia);
	~Enemigo();
	void virtual onColisionEnter(Objeto* contactObject);
	void virtual update();
	void draw();
	void stop();
	bool distancia();
	virtual void dropItems();
	virtual void comportamiento() {};
};
#endif
