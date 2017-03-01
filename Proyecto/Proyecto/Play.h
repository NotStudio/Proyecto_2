#pragma once
#include "EstadoPG.h"
class Play :
	public EstadoPG
{
public:
	Play(Juego * juego);
	virtual ~Play();

	virtual void draw();

	virtual void update();

private:

	Objeto* personaje;

	std::vector<Objeto*> enemigos;


};

