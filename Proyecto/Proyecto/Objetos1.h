#pragma once
#include "Boton.h"
#include "Crafteo.h"
class Objetos1 :
	public Crafteo
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

