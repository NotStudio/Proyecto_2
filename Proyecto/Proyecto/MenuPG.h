#ifndef MENU_H_
#define MENU_H_
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

#endif