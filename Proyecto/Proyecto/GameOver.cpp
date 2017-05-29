#include "GameOver.h"
#include "Play.h"
//#include "ZonaBase.h"



GameOver::GameOver(Juego* juego) : MenuJuego(juego)
{
	insertarBoton(Boton::ILUMINADO, 32, 32, playAgain, "Jugar de nuevo", "Intentalo otra vez, tu puedes");
	insertarBoton(Boton::ILUMINADO, 32, 40, quit, "Salir", "Sal perdiendo el culo como el cobarde que eres");
	Fondo = pJuego->getTextura("Gameover", "idle");
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
