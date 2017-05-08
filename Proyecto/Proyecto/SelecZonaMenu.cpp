#include "SelecZonaMenu.h"
#include "ZonaAccion.h"
#include "Play.h"

SelecZonaMenu::SelecZonaMenu(Juego* pJuego): MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");

	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 450, 100, goZona1, "Zona1"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 300, 250, goZona2, "Zona2"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 100, 330, goZona3, "Desguace"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 100, 530, salir, "Salir"));
}


SelecZonaMenu::~SelecZonaMenu()
{
}

void SelecZonaMenu::salir(Juego* pJuego) {	
	pJuego->popState();
}

void SelecZonaMenu::goZona1(Juego* pJuego) {

	pJuego->setZona("ZonaDesguace");
	Play::setZona();
	pJuego->popState();

}

void SelecZonaMenu::goZona2(Juego* pJuego) {

	goZona1(pJuego);
}

void SelecZonaMenu::goZona3(Juego* pJuego) {
	goZona1(pJuego);
}
