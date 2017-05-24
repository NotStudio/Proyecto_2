#include "MenuPG.h"
#include "Boton.h"
#include "Play.h"
#include "Opciones.h"

MenuPG::MenuPG(Juego * juego) :MenuJuego(juego)
{
	Fondo = juego->getTextura("MenuInicio", "idle");
	insertarBoton(Boton::FUTURISTA, 32, 20, playBase, "Jugar", "kek");
	insertarBoton(Boton::FUTURISTA, 32, 26, opciones, "Opciones", "kek");
	insertarBoton(Boton::FUTURISTA, 32, 32, salir, "Salir", "kek");
	
}


MenuPG::~MenuPG()
{
	
}


void MenuPG::salir(Juego * jg){
	jg->salir();
}

void MenuPG::cargar(Juego * jg){
}


void MenuPG::opciones(Juego * jg){
	jg->pushState(new Opciones(jg));


}

void MenuPG::playBase(Juego * jg){
	jg->changeState(new Play(jg));
}