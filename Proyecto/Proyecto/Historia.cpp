#include "Historia.h"
#include "MarcoHistorico.h"


Historia::Historia(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	botones.emplace_back(new BotonIluminado(pJuego,150, 150, marcoHis, "Historia", "Contexto historico"));
	//botones.emplace_back(new BotonIluminado(pJuego, 500, 100, toastyHis, "Pasado de Toasty", "Pasado de Toasty"));
	botones.emplace_back(new BotonIluminado(pJuego, 420, 150, salir, "Salir", "Vuelve a la base"));
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


