#include "Crafteo.h"
#include "Play.h"
#include "Objetos1.h"
#include "Objetos2.h"
#include "Objetos3.h"



Crafteo::Crafteo(Juego* pJuego) : EstadoPG(pJuego)
{
	botones.emplace_back(new Boton(pJuego, "boton", 50, 100, grado1, "1"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 250, grado2, "2"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 330, grado3, "3"));

	botones.emplace_back(new Boton(pJuego, "boton", 400, 300, salir, "Salir"));
}


Crafteo::~Crafteo()
{
}

void Crafteo::draw() {

	pJuego->getTextura("SelecMapaFondo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void Crafteo::update() {



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

void Crafteo::salir(Juego* pJuego) {


	pJuego->popState();


}

void Crafteo::grado1(Juego* pJuego) {

	pJuego->pushState(new Objetos1(pJuego));

}

void Crafteo::grado2(Juego* pJuego) {

	pJuego->pushState(new Objetos2(pJuego));
}

void Crafteo::grado3(Juego* pJuego) {
	
	pJuego->pushState(new Objetos3(pJuego));
}


