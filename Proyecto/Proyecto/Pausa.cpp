#include "Pausa.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
#include "Opciones.h"

Pausa::Pausa(Juego * juego) : MenuJuego(juego)//, pR(nullptr)
{
	pJuego->reproducirEfecto("Multiusos");
	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();

	insertarBoton(Boton::FUTURISTA, 32, 20, resume, "Continuar", "kek");
	insertarBoton(Boton::FUTURISTA, 32, 26, opciones, "Opciones", "kek");
	insertarBoton(Boton::FUTURISTA, 32, 32, returnMenu, "Vuelve al menu", "kek");
	Fondo = pJuego->getTextura("Pause", "idle");

	//Para añadir los botones
}


Pausa::~Pausa()
{
}


void Pausa::resume(Juego * jg){
	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popState();
}

void Pausa::returnMenu(Juego * jg){

	//jg->reiniciar();
	//jg->freeEstadoss();
	jg->changeState(new MenuPG(jg));
}

void Pausa::opciones(Juego * jg){
	jg->pushState(new Opciones(jg));
}
