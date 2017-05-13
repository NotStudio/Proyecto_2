#include "Crafteo.h"
#include "Play.h"
#include "Objetos1.h"
#include "Objetos2.h"
#include "Objetos3.h"



Crafteo::Crafteo(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	botones.emplace_back(new Boton(pJuego, "button", 50, 100, grado1, "Baul","Todos los objetos que en en baul"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 250, grado2, "Objetos Clave","Objetos para craftear objetos clave"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 330, grado3, "Objetos importantes","Objetos para Desbloquear otras zonas"));
	botones.emplace_back(new Boton(pJuego, "button", 400, 300, salir, "Salir","Vuelve a la base"));
}


Crafteo::~Crafteo()
{
}

void Crafteo::salir(Juego* pJuego) {


	pJuego->popState();


}

void Crafteo::grado1(Juego* pJuego) {

	pJuego->pushState(new Objetos1(pJuego));

}

void Crafteo::grado2(Juego* pJuego) {

	pJuego->pushState(new Objetos2(pJuego));
}

void Crafteo::grado3(Juego* pJuego) {
	
	pJuego->pushState(new Objetos3(pJuego));
}


