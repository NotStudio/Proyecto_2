#pragma once
#include "EstadoPG.h"
#include "Boton.h"
class Objetos3 :
	public EstadoPG
{

	std::vector <Boton*> botones;

	int activo = 0;

public:
	Objetos3(Juego* juego);
	virtual ~Objetos3();

	virtual void update();
	virtual void draw();
	static void salir(Juego* pjuego);

};

