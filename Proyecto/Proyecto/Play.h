#ifndef PLAY_H_
#define PLAY_H_

#include "EstadoPG.h"
#include "zonaJuego.h"
class Play :
	public EstadoPG
{
public:
	Play(Juego * juego);
	virtual ~Play();

	virtual void draw();

	virtual void update();

	//std::vector<Objeto*> extras;


private:

	Objeto* personaje;

	std::vector<Objeto*> enemigos;
	
	ZonaJuego* zona;

};

#endif