#include "Pausa.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"

Pausa::Pausa(Juego * juego) : EstadoPG(juego)//, pR(nullptr)
{

	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	botones.emplace_back(new Boton(juego, "boton", 300, 250, resume, "Continuar"));
	botones.emplace_back(new Boton(juego, "boton", 300, 350, returnMenu, "Salir"));

	//Para añadir los botones
}


Pausa::~Pausa()
{
	for (int i = 0; i < botones.size(); i++)
	{
		delete botones[i];
		botones[i] = nullptr;
	}
}


void Pausa::resume(Juego * jg){
	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popState();
}

void Pausa::returnMenu(Juego * jg){

	jg->freeEstadoss();
	jg->changeState(new MenuPG(jg));
}

void Pausa::draw() {
	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void Pausa::update() {

	botones[activo]->normal();
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < botones.size() - 1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	botones[activo]->aumentar();
	if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
		botones[activo]->accion();
	}
}
