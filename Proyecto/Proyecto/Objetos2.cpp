#include "Objetos2.h"


Objetos2::Objetos2(Juego* pJuego) : EstadoPG(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "boton", 50, 50, nullptr, "Engranaje"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 100, nullptr, "Carbono"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 150, nullptr, "Engranajes"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 200, nullptr, "Tanque Presion"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 250, nullptr, "Refinador"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 300, nullptr, "Circuito"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 350, nullptr, "B.Iones"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 400, nullptr, "S.Movimiento"));
	botones.emplace_back(new Boton(pJuego, "boton", 400, 300, salir, "Salir"));

}


Objetos2::~Objetos2()
{
}

void Objetos2::draw() {

	pJuego->getTextura("SelecMapaFondo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void Objetos2::update() {



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


void Objetos2::salir(Juego* pJuego) {


	pJuego->popState();


}

