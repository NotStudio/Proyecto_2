#include "SelecZonaMenu.h"
#include "ZonaAccion.h"
#include "Play.h"

SelecZonaMenu::SelecZonaMenu(Juego* pJuego): MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();


	botones.emplace_back(new BotonMecanico(pJuego, 450, 100, goZona1, "Bosque"));
	botones.emplace_back(new BotonMecanico(pJuego,300, 250, goZona2, "Desguace"));
	botones.emplace_back(new BotonMecanico(pJuego,100, 330, goZona3, "Zona3"));
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");

	botones.emplace_back(new BotonFuturista(pJuego, 100, 530, salir, "Salir"));
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
	goZona1(pJuego);
}

