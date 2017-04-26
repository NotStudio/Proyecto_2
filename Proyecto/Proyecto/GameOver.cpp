#include "GameOver.h"
#include "Play.h"
//#include "ZonaBase.h"



GameOver::GameOver(Juego* juego) : EstadoPG(juego)
{
	botones.emplace_back(new Boton(juego, "boton", 415, 175, playAgain, "Jugar de nuevo"));
	botones.emplace_back(new Boton(juego, "boton", 415, 275, quit, "Salir"));

}


GameOver::~GameOver()
{
	for (int i = 0; i < botones.size(); i++)
	{
		delete botones[i];
		botones[i] = nullptr;
	}
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

void GameOver::draw() {
	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void GameOver::update() {

	botones[activo]->normal();
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < botones.size() - 1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	botones[activo]->aumentar();
	if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
		botones[activo]->accion();
	}
}