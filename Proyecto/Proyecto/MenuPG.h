#ifndef MENU_H_
#define MENU_H_
#include "EstadoPG.h"
#include "Boton.h"

//Clase inicio...
class MenuPG :
	public EstadoPG
{
public:
	MenuPG(Juego * juego);
	virtual ~MenuPG();

private:
	std::vector <Boton*> botones;

	int activo = 0;
	static void salir(Juego * jg);
	static void playBase(Juego * jg);
	static void cargar(Juego* jg);
	virtual void update();
	virtual void draw();

};

#endif