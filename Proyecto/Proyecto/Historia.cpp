#include "Historia.h"
#include "MarcoHistorico.h"


Historia::Historia(Juego* pJuego) : MenuJuego(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "button", 150, 150, marcoHis, "Historia", "Contexto historico"));
	//botones.emplace_back(new Boton(pJuego, "button", 500, 100, toastyHis, "Pasado de Toasty", "Pasado de Toasty"));
	botones.emplace_back(new Boton(pJuego, "button", 420, 150, salir, "Salir", "Vuelve a la base"));
	Fondo = pJuego->getTextura("SelectorHistoria", "idle");

}


Historia::~Historia()
{
}


void Historia::salir(Juego* pJuego) {


	pJuego->popState();


}

void Historia::marcoHis(Juego* pJuego) {

	pJuego->pushState(new MarcoHistorico(pJuego));

}

/*void Historia::toastyHis(Juego* pJuego) {

	pJuego->pushState(new (pJuego));
}*/


