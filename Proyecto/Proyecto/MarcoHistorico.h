#pragma once
#include "Historia.h"
#include "Boton.h"

class MarcoHistorico : public MenuJuego
{
public:
	MarcoHistorico(Juego* pJuego);
	virtual ~MarcoHistorico();

	
	map<string, bool> memorias;
	TexturasSDL * imgObj;
	TextoSDL Texto;

protected:
	virtual void update();
	virtual void draw();
	static void salir(Juego * jg);
	
};

