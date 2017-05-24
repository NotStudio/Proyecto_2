#include "MarcoHistorico.h"


MarcoHistorico::MarcoHistorico(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelectorHistoria", "idle");
	memorias = pJuego->getMemoria();
	int contX = 0;
	int contY = 1;
	botones.emplace_back(new BotonIluminado(pJuego, 420, 150, salir, "Salir", "Vuelve a historia"));

	for (map<string, bool>::iterator it = memorias.begin(); it != memorias.end(); it++)
	{
		if (it->second){
			botones.emplace_back(new BotonIluminado(pJuego, contX * 170 + 20, contY * 50, salir, it->first));
			contY++;
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
		//imgObj->draw(pJuego->getRender(), SDL_Rect{ 530, 50, 125, 125 }, nullptr);
	}
}


void MarcoHistorico::salir(Juego* pJuego) {
	pJuego->popState();
}