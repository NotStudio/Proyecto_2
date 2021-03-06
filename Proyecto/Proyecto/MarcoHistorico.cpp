#include "MarcoHistorico.h"


MarcoHistorico::MarcoHistorico(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelectorHistoria2", "idle");
	memorias = pJuego->getMemoria();
	int contX = 0;
	int contY = 1;
	
	for (map<string, bool>::iterator it = memorias.begin(); it != memorias.end(); it++)
	{
		if (it->second){
			insertarBoton(Boton::ILUMINADOBLANCO, 13, 11 + contY, salir, it->first, "kek");
			contY += 5;
			
		}
	}
	insertarBoton(Boton::ILUMINADOBLANCO, 13, 50, salir, "Salir", "Vuelve a historia");
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
		imgObj->draw(pJuego->getRender(), SDL_Rect{ pJuego->getWindow().ancho / 2 - pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto / 2 - pJuego->getWindow().alto * 0.4, 800, 600 }, nullptr);
	}
}


void MarcoHistorico::salir(Juego* pJuego) {
	pJuego->popState();
}