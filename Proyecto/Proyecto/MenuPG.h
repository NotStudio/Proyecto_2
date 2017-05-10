#ifndef MENU_H_
#define MENU_H_
#include "MenuJuego.h"
#include "Boton.h"

//Clase inicio...
class MenuPG :
	public MenuJuego
{
public:
	MenuPG(Juego * juego);
	virtual ~MenuPG();

private:
	static void salir(Juego * jg);
	static void playBase(Juego * jg);
	static void cargar(Juego* jg);

};

#endif