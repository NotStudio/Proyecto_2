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

	void draw();
	void update();
	void onClick();

protected:

	Juego* ptsjuego;

	std::vector <Objeto*> objetos;  

};

