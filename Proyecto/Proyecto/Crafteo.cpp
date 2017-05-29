#include "Crafteo.h"
#include "Play.h"
#include "Objetos1.h"
#include "Objetos2.h"
#include "Objetos3.h"



Crafteo::Crafteo(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Fondo = pJuego->getTextura("HudCraft", "idle");
	insertarBoton(Boton::ILUMINADO, 30, 10, grado1, "Baul", "caja de objetos");
	insertarBoton(Boton::ILUMINADO, 15, 30, grado2, "Nivel 1", "craftea entre 2 objetos");
	insertarBoton(Boton::ILUMINADO, 45, 30, grado3, "Nivel 2", "craftea entre 3 objetos");
	insertarBoton(Boton::ILUMINADO, 50, 55, salir, "Salir", "volver a base");
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


