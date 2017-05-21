#pragma once

#include "MenuJuego.h"
#include "Boton.h"

//Clase inicio...
class Opciones :
	public MenuJuego
{
public:
	Opciones(Juego * juego);
	virtual ~Opciones();

private:
	static void salir(Juego * jg);
	static void playBase(Juego * jg);
	static void sube(Juego* jg);
	static void baja(Juego* jg);
};
