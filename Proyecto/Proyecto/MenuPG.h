#pragma once
#include "EstadoPG.h"

//Clase inicio...
class MenuPG :
	public EstadoPG
{
public:
	MenuPG(Juego * juego);
	virtual ~MenuPG();

private:
	static void salir(Juego * jg);
	static void playBase(Juego * jg);
	static void cargar(Juego* jg);

};

