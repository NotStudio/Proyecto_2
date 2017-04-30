#include "Objetos3.h"


Objetos3::Objetos3(Juego* pJuego) : EstadoPG(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "boton", 50, 50, nullptr, "Mecanismo"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 100, nullptr, "C.Electrico"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 150, nullptr, "Combustible"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 200, nullptr, "F.Carbono"));
	botones.emplace_back(new Boton(pJuego, "boton", 400, 300, salir, "Salir"));
}


Objetos3::~Objetos3()
{
}

void Objetos3::draw() {

	pJuego->getTextura("SelecMapaFondo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void Objetos3::update() {



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


void Objetos3::salir(Juego* pJuego) {


	pJuego->popState();


}

