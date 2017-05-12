#include "Historia.h"
#include "MarcoHistorico.h"


Historia::Historia(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
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


