#pragma once
#include "Boton.h"
#include "Crafteo.h"
class Objetos1 :
	public MenuJuego
{
	map<string, int> Baul;
	vector<int> cantidad;
	TexturasSDL * imgObj;
	TextoSDL Texto;

public:
	Objetos1(Juego* juego);
	virtual ~Objetos1();

	virtual void update();
	virtual void draw();
	static void salir(Juego* pjuego);
};

