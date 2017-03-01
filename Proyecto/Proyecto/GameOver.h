#pragma once
#include "EstadoPG.h"


class GameOver :
	public EstadoPG
{
public:
	GameOver(Juego* juego);
	virtual ~GameOver();

private:
	
	static void base(Juego* jg);
	
	// cuando mueres sale un boton para ir a la base

};

 
