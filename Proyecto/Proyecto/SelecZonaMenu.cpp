#include "SelecZonaMenu.h"
#include "ZonaAccion.h"
#include "Play.h"

SelecZonaMenu::SelecZonaMenu(Juego* pJuego): MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	pJuego->reproducirEfecto("Multiusos");
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	insertarBoton(Boton::MECANICO, 15, 10, goZona1, "The Natural Preserve");
	insertarBoton(Boton::MECANICO, 28, 25, goZona2, "Several Motors");
	insertarBoton(Boton::MECANICO, 9, 40, goZona3, "Hipsters Sanctuary");
	insertarBoton(Boton::MECANICO, 50, 50, salir, "Salir", "kek");
}


SelecZonaMenu::~SelecZonaMenu()
{
}

void SelecZonaMenu::salir(Juego* pJuego) {	
	pJuego->popState();
}

void SelecZonaMenu::goZona1(Juego* pJuego) {

	pJuego->setZona("ZonaBosque");
	Play::setZona();
	pJuego->popState();

}

void SelecZonaMenu::goZona2(Juego* pJuego) {

	pJuego->setZona("ZonaDesguace");
	Play::setZona();
	pJuego->popState();
}

void SelecZonaMenu::goZona3(Juego* pJuego) {

	pJuego->setZona("ZonaPinApple");
	Play::setZona();
	pJuego->popState();
}

