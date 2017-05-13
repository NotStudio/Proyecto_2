#include "Pausa.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"

Pausa::Pausa(Juego * juego) : MenuJuego(juego)//, pR(nullptr)
{
	pJuego->reproducirEfecto("Multiusos");
	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	botones.emplace_back(new Boton(juego, "button", 300, 250, resume, "Continuar","Continua jugando"));
	botones.emplace_back(new Boton(juego, "button", 300, 350, returnMenu, "Salir", "Vuelve al menu"));

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

	jg->freeEstadoss();
	jg->changeState(new MenuPG(jg));
}
