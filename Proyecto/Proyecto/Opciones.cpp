#include "Opciones.h"
#include "Boton.h"
#include "Play.h"

Opciones::Opciones(Juego * juego) :MenuJuego(juego)
{
	Fondo = juego->getTextura("MenuInicio", "idle");
	botones.emplace_back(new BotonFuturista(juego, 400, 175, playBase, "Volver", "Comeback to the fucking game"));
	botones.emplace_back(new BotonFuturista(juego, 400, 275, sube, "Subir Volumen", "Sube el volumen locaso"));
	botones.emplace_back(new BotonFuturista(juego, 400, 375, baja, "Bajar Volumen", "Baja el volumen locaso"));
	botones.emplace_back(new BotonFuturista(juego, 400, 475, salir, "Salir", "Get out of my fucking game"));
}


Opciones::~Opciones()
{

}


void Opciones::salir(Juego * jg){
	jg->salir();
}

void Opciones::sube(Juego * jg){
	jg->masVolumen();
}

void Opciones::baja(Juego * jg){
	jg->menosVolumen();
}

void Opciones::playBase(Juego * jg){
	jg->popState();
}