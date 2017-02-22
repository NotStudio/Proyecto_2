#include "MenuPG.h"
//#include "Boton.h"


MenuPG::MenuPG(Juego * juego) :Estado(juego)
{
	objetos.emplace_back(new Boton(ptsjuego, Juego::BSalir, 500, 400, salir));
	objetos.emplace_back(new Boton(ptsjuego, Juego::BJugar, 200, 400, play));

}


MenuPG::~MenuPG()
{
}


void MenuPG::salir(Juego * jg){
	jg->setSalir();
}

void MenuPG::play(Juego * jg){
	jg->changeState(new Play(jg));
}
