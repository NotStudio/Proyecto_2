#include "FinalJuego.h"
#include "MenuPG.h"

FinalJuego::FinalJuego(Juego* pJuego) : MenuJuego(pJuego)
{

	//Cambiar fondo al de final del juego
	Fondo = pJuego->getTextura("SelectorHistoria1", "idle");

	insertarBoton(Boton::FUTURISTA, 41, 48, salir, "Salir", "Vuelve a la base");
	insertarBoton(Boton::FUTURISTA, 21, 48, menu, "Menú", "Vuelve al menu");


}


FinalJuego::~FinalJuego()
{
}

void FinalJuego::menu(Juego* pJuego) {


	pJuego->changeState(new MenuPG(pJuego));


}
void FinalJuego::salir(Juego* pJuego) {


	pJuego->popState();


}
