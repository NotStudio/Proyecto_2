#pragma once
#include "EstadoPG.h"
#include "Boton.h"
class Objetos2 :
	public EstadoPG
{

	std::vector <Boton*> botones;

	int activo = 0;

public:
	Objetos2(Juego* juego);
	virtual ~Objetos2();

	virtual void update();
	virtual void draw();
	static void salir(Juego* pjuego);
};

