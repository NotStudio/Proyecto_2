#include "GameOver.h"



GameOver::GameOver(Juego* juego) : EstadoPG(juego)
{
	objetos.emplace_back(new Boton(ptsjuego, Juego::Bbase, 500, 400, menu));
}


GameOver::~GameOver()
{
}



void GameOver::base(Juego * jg){
	jg->changeState(new /* base(jg)*/);
}