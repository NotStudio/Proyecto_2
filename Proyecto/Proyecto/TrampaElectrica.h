#ifndef CABLEADO_H
#define CABLEADO_H
#include "Enemigo.h"
class TrampaElectrica :
	public Enemigo
{
	int cadencia;
	bool activated;
	bool needChange;
	void alternaActivo();
public:
	TrampaElectrica(Juego* punteroJuego, int x, int y);
	virtual ~TrampaElectrica();

	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void comportamiento();
	uint32 changeState() { activated = !activated; needChange = true; return 0; };
	//virtual void desactivar();
};

#endif CABLEADO_H