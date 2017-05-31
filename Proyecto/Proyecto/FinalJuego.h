#pragma once
#include "MenuJuego.h"
class FinalJuego :
	public MenuJuego
{
public:
	FinalJuego(Juego* pJuego);
	virtual ~FinalJuego();
private:
	static void menu(Juego * jg);
	static void salir(Juego * jg);
	
};

