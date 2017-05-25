#include "MarcoHistorico.h"


MarcoHistorico::MarcoHistorico(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelectorHistoria", "idle");
	memorias = pJuego->getMemoria();
	int contX = 0;
	int contY = 1;
	insertarBoton(Boton::ILUMINADO, 55, 63, salir, "Salir", "Vuelve a historia");
	
	for (map<string, bool>::iterator it = memorias.begin(); it != memorias.end(); it++)
	{
		if (it->second){
			insertarBoton(Boton::ILUMINADO, 17, 11 + contY, salir, it->first, "kek");
			contY += 4;
			if (contY == 6) {
				contY = 1;
				contX++;
			}
		}
	}
	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));
	imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");

}


MarcoHistorico::~MarcoHistorico()
{
}


void MarcoHistorico::update(){
	MenuJuego::update();
}

void MarcoHistorico::draw(){
	MenuJuego::draw();
	if (botones[activo]->getNombre() != "Salir") {
		imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		imgObj->draw(pJuego->getRender(), SDL_Rect{ pJuego->getWindow().ancho / 2 + 100, pJuego->getWindow().alto / 2 - 200, 500, 600 }, nullptr);
	}
}


void MarcoHistorico::salir(Juego* pJuego) {
	pJuego->popState();
}