#include "Crafteo.h"
#include "Play.h"
#include "Objetos1.h"
#include "Objetos2.h"
#include "Objetos3.h"



Crafteo::Crafteo(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Fondo = pJuego->getTextura("SelecCrafteoFondo", "idle");
	insertarBoton(Boton::ILUMINADO, 10, 10, grado1, "Baul", "caja de objetos");
	insertarBoton(Boton::ILUMINADO, 10, 20, grado2, "Crafteo 2", "craftea entre 2 objetos");
	insertarBoton(Boton::ILUMINADO, 10, 30, grado3, "Crafteo 3", "craftea entre 3 objetos");
	insertarBoton(Boton::ILUMINADO, 10, 40, salir, "Salir", "volver a base");
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


