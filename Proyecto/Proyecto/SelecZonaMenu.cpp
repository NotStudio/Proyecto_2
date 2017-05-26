#include "SelecZonaMenu.h"
#include "ZonaAccion.h"
#include "Play.h"

SelecZonaMenu::SelecZonaMenu(Juego* pJuego): MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	pJuego->reproducirEfecto("Multiusos");
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	insertarBoton(Boton::MECANICO, 15, 10, goZona1, "Bosque");
	insertarBoton(Boton::MECANICO, 28, 25, goZona2, "Desguace");
	insertarBoton(Boton::MECANICO, 9, 40, goZona3, "Zona3");
	insertarBoton(Boton::MECANICO, 55, 63, salir, "Salir", "kek");
}


SelecZonaMenu::~SelecZonaMenu()
{
}

void SelecZonaMenu::salir(Juego* pJuego) {	
	pJuego->popState();
}

void SelecZonaMenu::goZona1(Juego* pJuego) {

	pJuego->setZona("ZonaTutorial");
	Play::setZona();
	pJuego->popState();

}

void SelecZonaMenu::goZona2(Juego* pJuego) {

	pJuego->setZona("ZonaDesguace");
	Play::setZona();
	pJuego->popState();
}

void SelecZonaMenu::goZona3(Juego* pJuego) {
	goZona1(pJuego);
}

