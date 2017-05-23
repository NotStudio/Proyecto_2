#include "GameOver.h"
#include "Play.h"
//#include "ZonaBase.h"



GameOver::GameOver(Juego* juego) : MenuJuego(juego)
{
	botones.emplace_back(new BotonIluminado(juego, 415, 175, playAgain, "Jugar de nuevo", "Intentalo otra vez, tu puedes"));
	botones.emplace_back(new BotonIluminado(juego, 415, 275, quit, "Salir", "Sal perdiendo el culo como el cobarde que eres"));
}


GameOver::~GameOver()
{
}



void GameOver::playAgain(Juego * jg){
	//jg->changeState(new Play(jg));
	jg->reiniciar();
	jg->setZona("ZonaBase");
	Play::setZona();
	jg->popState();

}

void GameOver::quit(Juego * jg){
	jg->salir();
}
