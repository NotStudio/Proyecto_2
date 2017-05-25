#include "Opciones.h"
#include "Boton.h"
#include "Play.h"

Opciones::Opciones(Juego * juego) :MenuJuego(juego)
{
	Fondo = juego->getTextura("MenuInicio", "idle");
	insertarBoton(Boton::FUTURISTA, 37, 20, playBase, "Volver", "kek");
	insertarBoton(Boton::FUTURISTA, 37, 26, sube, "Subir Volumen", "kek");
	insertarBoton(Boton::FUTURISTA, 37, 32, baja, "Bajar Volumen", "kek");
	insertarBoton(Boton::FUTURISTA, 37, 38, salir, "Salir", "kek");
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