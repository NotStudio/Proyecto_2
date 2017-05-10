#ifndef	ZONABOSQUE_H
#define ZONABOSQUE_H
#include "ZonaAccion.h"
class ZonaBosque :
	public ZonaAccion
{
public:
	ZonaBosque(Juego* punteroJuego);
	virtual ~ZonaBosque();
};

#endif //ZONABOSQUE_H