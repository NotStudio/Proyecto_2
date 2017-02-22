#include "Pausa.h"


Pausa::Pausa(Juego * juego) : EstadoPG(juego)
{
	/*objetos.emplace_back(new Boton(ptsjuego, JuegoPG::BContinuar, 200, 400, resume));
	objetos.emplace_back(new Boton(ptsjuego, JuegoPG::BMenu, 500, 400, menu));*/

	//Para añadir los botones
}


Pausa::~Pausa()
{
}


void Pausa::resume(Juego * jg){
	jg->popState();
}

void Pausa::menu(Juego * jg){
	jg->changeState(new MenuPG(jg));
}
