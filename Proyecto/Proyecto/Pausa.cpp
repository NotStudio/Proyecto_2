#include "Pausa.h"


Pausa::Pausa(Juego * juego) : EstadoPG(juego)
{
//	objetos.emplace_back(new Boton(ptsjuego, Juego::BContinuar, 200, 400, resume));
//	objetos.emplace_back(new Boton(ptsjuego, Juego::BMenu, 500, 400, base));

	//Para añadir los botones
}


Pausa::~Pausa()
{
}


void Pausa::resume(Juego * jg){
	//jg->popState();
}

void Pausa::base(Juego * jg){
//	jg->changeState(new Base(jg));
}
