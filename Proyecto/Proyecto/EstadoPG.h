#pragma once
#include "EstadoJuego.h"
#include "Juego.h"
#include "Objeto.h"

class EstadoPG :
	public EstadoJuego
{
public:
	EstadoPG(Juego * juego);
	virtual ~EstadoPG();

	virtual void draw();
	virtual void update();

protected:

	Juego* ptsjuego;

	std::vector <Objeto*> objetos;  

};

