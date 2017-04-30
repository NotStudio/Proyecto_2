#pragma once
#include "EstadoPG.h"
#include "Boton.h"
class Objetos1 :
	public EstadoPG
{

	std::vector <Boton*> botones;

	int activo = 0;

	

	Juego::Animacion animacion;
public:
	Objetos1(Juego* juego);
	virtual ~Objetos1();

	virtual void update();
	virtual void draw();
	static void salir(Juego* pjuego);
};

