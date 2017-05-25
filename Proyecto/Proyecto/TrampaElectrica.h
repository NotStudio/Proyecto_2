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
	uint32 timerInmune;
public:
	TrampaElectrica(Juego* punteroJuego, int x, int y);
	virtual ~TrampaElectrica();

	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	virtual void comportamiento();
	uint32 changeState() {
		activated = !activated;
		if (activated)
			Mix_PlayChannelTimed(-1, pJuego->cargarEfecto("electricidad"), 0, cadencia);

		needChange = true;
		return 0;
	};
	//virtual void desactivar();
};

#endif CABLEADO_H