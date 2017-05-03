#include "SelecZonaMenu.h"
#include "ZonaAccion.h"
#include "Play.h"

int SelecZonaMenu::seleccion = NEUTRO;

SelecZonaMenu::SelecZonaMenu(Juego* pJuego): EstadoPG(pJuego)
{
	

	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 450, 100, goZona1, "Zona1"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 300, 250, goZona2, "Zona2"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 100, 330, goZona3, "Desguace"));
	botones.emplace_back(new Boton(pJuego, "buttonSelecZona", 100, 530, salir, "Salir"));
}


SelecZonaMenu::~SelecZonaMenu()
{

	for (int i = 0; i < botones.size(); i++)
	{
		delete botones[i];
		botones[i] = nullptr;
	}
}

void SelecZonaMenu::draw() {

	pJuego->getTextura("SelecMapaFondo", "idle")->draw(pJuego->getRender(), SDL_Rect{0,0,800,600}, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void SelecZonaMenu::update() {

	

	botones[activo]->normal();
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < botones.size() - 1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	botones[activo]->aumentar();
	if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
		botones[activo]->accion();
	}
	doCallBack();
}

void SelecZonaMenu::salir(Juego* pJuego) {

	
	SelecZonaMenu::seleccion = SALIR;
	

}

void SelecZonaMenu::goZona1(Juego* pJuego) {

	seleccion = ZONA1;

}

void SelecZonaMenu::goZona2(Juego* pJuego) {

	goZona1(pJuego);
}

void SelecZonaMenu::goZona3(Juego* pJuego) {
	goZona1(pJuego);
}

void SelecZonaMenu::doCallBack() {

	switch (seleccion)
	{
	case NEUTRO:
		break;
	case SALIR:
		SelecZonaMenu::seleccion = NEUTRO;
		pJuego->popState();
		break;
	case ZONA1:
		SelecZonaMenu::seleccion = NEUTRO;
		pJuego->setZona("ZonaDesguace");
		Play::setZona();
		pJuego->popState();
		break;
	case ZONA2:
		break;
	case ZONA3:
		break;
	default:
		break;
	}

}