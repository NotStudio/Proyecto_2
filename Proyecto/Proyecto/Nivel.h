#pragma once
#include <vector>
#include "NPC.h"

class Nivel
{
public:
	Nivel();
	virtual ~Nivel();

	std::vector<Objeto*> getEnemigos();

	std::vector<Objeto*> getObjetos();

	

private:

	std::vector<Objeto*> enemigos;

	std::vector<Objeto*> objetos;

	//Juego::Animacion anim;

	//Dificultad.
	
};

