#include "Objetos1.h"



Objetos1::Objetos1(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Baul = pJuego->getBaul()->getMap();
	Fondo = pJuego->getTextura("HudCraft", "idle");
	int contX = 0;
	int contY = 1;

	for (map<string, int>::iterator it = Baul.begin(); it != Baul.end(); it++)
	{
		if (it->second > 0) {
			botones.emplace_back(new Boton(pJuego, "button", contX * 170 + 20, contY * 50, salir, it->first));
			contY++;
			if (contY == 6) {
				contY = 1;
				contX++;
			}
			cantidad.emplace_back(it->second);
		}
	}
	botones.emplace_back(new Boton(pJuego, "button", 565, 470, salir, "Salir"));
	if (cantidad.size() > 0) {
		cantidad.emplace_back(cantidad[cantidad.size() - 1]);
		imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));

		Texto.loadTexto(pJuego->getRender(), std::to_string(cantidad[activo]));
	}

}


Objetos1::~Objetos1()
{
}

void Objetos1::draw() {
	MenuJuego::draw();
	if (botones[activo]->getNombre() != "Salir") {
		imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		imgObj->draw(pJuego->getRender(), SDL_Rect{ 530, 50, 125, 125 }, nullptr);

		Texto.loadTexto(pJuego->getRender(), std::to_string(cantidad[activo]));
		Texto.draw(pJuego->getRender(), 650, 75);
	}
	
}

void Objetos1::update() {
	MenuJuego::update();
}


void Objetos1::salir(Juego* pJuego) {

	pJuego->popState();

}
