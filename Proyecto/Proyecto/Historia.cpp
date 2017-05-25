#include "Historia.h"
#include "MarcoHistorico.h"


Historia::Historia(Juego* pJuego) : MenuJuego(pJuego)
{

	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	
	insertarBoton(Boton::ILUMINADO, 21, 18, marcoHis, "Historia", "Contexto historico");
	insertarBoton(Boton::ILUMINADO, 31, 18, salir, "Salir", "Vuelve a la base");
	
	//botones.emplace_back(new BotonIluminado(pJuego, 500, 100, toastyHis, "Pasado de Toasty", "Pasado de Toasty"));

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


