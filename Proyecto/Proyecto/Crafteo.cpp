#include "Crafteo.h"
#include "Play.h"
#include "Objetos1.h"
#include "Objetos2.h"
#include "Objetos3.h"



Crafteo::Crafteo(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	botones.emplace_back(new Boton(pJuego, "button", 50, 100, grado1, "Ba�l","Objetos que tienes guardados"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 250, grado2, "Objetos Clave","Objetos de grado 2"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 330, grado3, "Objetos Hist�ricos","Objetos de grado 3"));
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


