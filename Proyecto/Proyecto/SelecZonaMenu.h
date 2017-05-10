#ifndef SELECT_ZONA_MENU_H
#define SELECT_ZONA_MENU_H
#include "EstadoPG.h"
#include "Boton.h"
#include "MenuJuego.h"

class SelecZonaMenu :
	public MenuJuego
{
	static void salir(Juego * jg);
	static void goZona1(Juego* jg);
	static void goZona2(Juego* jg);
	static void goZona3(Juego* jg);
	
	enum zonaSelec { ZONA1, ZONA2, ZONA3, SALIR, NEUTRO };
	

public:
	SelecZonaMenu(Juego* jg);
	virtual ~SelecZonaMenu();
};

#endif //SELECT_ZONA_MENU_H