#include "Objetos1.h"


Objetos1::Objetos1(Juego* pJuego) : Crafteo(pJuego)
{
	
	botones.emplace_back(new Boton(pJuego, "button", 20, 50, nullptr, "Chatarra"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 100, nullptr, "Madera"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 150, nullptr, "Tuercas"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 200, nullptr, "Carbon"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 250, nullptr, "Petroleo"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 300, nullptr, "Tanque"));
	
	botones.emplace_back(new Boton(pJuego, "button", 190, 50, nullptr, "Tuberias"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 100, nullptr, "Estanyo"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 150, nullptr, "Litio"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 200, nullptr, "Chip"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 250, nullptr, "Sensor"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 300, nullptr, "Fusible"));
	botones.emplace_back(new Boton(pJuego, "button", 565, 470, salir, "Salir"));

	animacion.loadTextura(pJuego->getTextura(botones[0]->getNombre(), "idle"));

	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));

}


Objetos1::~Objetos1()
{
}

void Objetos1::draw() {

	pJuego->getTextura("HudCraft", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();

		
		
	}

	if (botones[activo]->getNombre() != "Salir"){
		animacion.textura = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 530, 50, 125, 125 }, animacion.currentRect(), 0.0);

		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){

			Texto.loadTexto(pJuego->getRender(), "0");
			Texto.draw(pJuego->getRender(), 650, 75);
		}
		else{
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 650, 75);
			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
		}
	}
	
	
}

void Objetos1::update() {



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


void Objetos1::salir(Juego* pJuego) {


	pJuego->popState();


}
