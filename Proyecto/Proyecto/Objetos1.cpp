#include "Objetos1.h"



Objetos1::Objetos1(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Baul = pJuego->getBaul()->getMap();
	Fondo = pJuego->getTextura("HudCraft", "idle");
	int contX = 0;
	int contY = 0;

	for (map<string, int>::iterator it = Baul.begin(); it != Baul.end(); it++)
	{
		if (it->second > 0) {
			insertarBoton(Boton::ILUMINADO, 10 + contX * 7, 11 + contY * 5 ,salir,it->first);
			contY++;
			if (contY == 7) {
				contY = 0;
				contX++;
			}
			cantidad.emplace_back(it->second);
		}
	}
	insertarBoton(Boton::ILUMINADO, 50, 55, salir, "Salir");
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
		imgObj->draw(pJuego->getRender(), SDL_Rect{ 40 * fx, 20 * fy, 250, 250 }, nullptr);

		Texto.loadTexto(pJuego->getRender(), std::to_string(cantidad[activo]));
		Texto.draw(pJuego->getRender(), 38 * fx, fy * 20);
	}
	
}

void Objetos1::update() {
	MenuJuego::update();
}


void Objetos1::salir(Juego* pJuego) {

	pJuego->popState();

}
