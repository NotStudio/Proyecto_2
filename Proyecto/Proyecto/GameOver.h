#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include "MenuJuego.h"
#include "Boton.h"


class GameOver :
	public MenuJuego
{
public:
	GameOver(Juego* juego);
	virtual ~GameOver();

private:
	static void playAgain(Juego * jg);
	static void quit(Juego * jg);
};


#endif