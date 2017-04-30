#include "Cambio.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"

Cambio::Cambio(Juego * juego,int actual,int Personajes) : EstadoPG(juego)//, pR(nullptr)
{
	personajes = Personajes;
	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();

	activo = actual;
	boton = (new Boton(juego, "boton", 300, 250, resume, "Continuar"));

	//Para añadir los botones
}


Cambio::~Cambio()
{
	
	delete boton;
		boton = nullptr;
	
}



void Cambio::resume(Juego * jg){

	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popStateandCamera();
}



void Cambio::draw() {
	boton->draw();
}

void Cambio::update() {

	
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < personajes-1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	

	else if (pJuego->inputQuery(SDL_SCANCODE_RETURN)) {
		activar(pJuego);
		boton->accion();




	}
	cout << "Personaje " << activo << endl;
}
