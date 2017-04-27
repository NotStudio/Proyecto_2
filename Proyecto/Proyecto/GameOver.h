#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include "EstadoPG.h"
#include "Boton.h"


class GameOver :
	public EstadoPG
{
public:
	GameOver(Juego* juego);
	virtual ~GameOver();

private:



	int activo = 0;
	std::vector <Boton*> botones;

	static void playAgain(Juego * jg);
	static void quit(Juego * jg);

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
	virtual void update();
	virtual void draw();
};


#endif