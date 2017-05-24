#ifndef ENEMIGO_H_
#define ENEMIGO_H_
#include "ZonaAccion.h"

#include "NPC.h"
class Enemigo : public NPC
{
protected:

	int _distancia;

	bool needDrop;
	bool isDead_;
	bool noDeadAnim = false;
	bool isKillable;
	virtual void muerte();
	virtual void comportamiento() {};
	void nextFrame(){
		currentAnim->ActualizarFrame();
	}
public:
	Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia);
	~Enemigo();
	void virtual onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	void virtual update();
	void draw();
	void stop();
	bool distancia();
	virtual void dropItems();
	virtual void desactivar();
	bool killable() { return isKillable; };
	bool isDead() { return destruido; }
	int getDanyoContacto(){ return stats.daño; }
};
#endif
