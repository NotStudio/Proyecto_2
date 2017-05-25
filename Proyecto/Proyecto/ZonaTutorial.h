#ifndef ZONA_TUTORIAL_H
#define ZONA_TUTORIAL_H
#include "ZonaAccion.h"
class ZonaTutorial :
	public ZonaAccion
{
	TextoSDL texto1_;
	TextoSDL texto2_;
	string frase1_, frase2_;
	float timerTexto_;

	void setTextos();

	void updateTextos();
public:
	ZonaTutorial(Juego* j);
	virtual ~ZonaTutorial();

	virtual void draw();
	virtual void update();
};
#endif //ZONA_TUTORIAL_H
