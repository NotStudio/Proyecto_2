#ifndef SELECT_ZONA_MENU_H
#define SELECT_ZONA_MENU_H
#include "EstadoPG.h"
#include "Boton.h"

class SelecZonaMenu :
	public EstadoPG
{

	std::vector <Boton*> botones;

	

	int activo = 0;
	static int seleccion;
	static void salir(Juego * jg);
	static void goZona1(Juego* jg);
	static void goZona2(Juego* jg);
	static void goZona3(Juego* jg);
	
	enum zonaSelec { ZONA1, ZONA2, ZONA3, SALIR, NEUTRO };
	void doCallBack();
	

public:
	SelecZonaMenu(Juego* jg);
	virtual ~SelecZonaMenu();
	virtual void update();
	virtual void draw();
};

#endif //SELECT_ZONA_MENU_H