#include "MarcoHistorico.h"


MarcoHistorico::MarcoHistorico(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelectorHistoria2", "idle");
	memorias = pJuego->getMemoria();
	int contX = 0;
	int contY = 1;
	insertarBoton(Boton::ILUMINADO, 47, 50, salir, "Salir", "Vuelve a historia");
	
	for (map<string, bool>::iterator it = memorias.begin(); it != memorias.end(); it++)
	{
		if (it->second){
			insertarBoton(Boton::ILUMINADO, 13, 11 + contY, salir, it->first, "kek");
			contY += 4.6;
			
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
	if (botones[activo]->getNombre() != "Salir") {
		imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");
	}
}

void MarcoHistorico::draw(){
	MenuJuego::draw();
	if (botones[activo]->getNombre() != "Salir") {
		imgObj->draw(pJuego->getRender(), SDL_Rect{ pJuego->getWindow().ancho / 2 - pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto / 2 - pJuego->getWindow().alto * 0.3, 800, 600 }, nullptr);
	}
}


void MarcoHistorico::salir(Juego* pJuego) {
	pJuego->popState();
}