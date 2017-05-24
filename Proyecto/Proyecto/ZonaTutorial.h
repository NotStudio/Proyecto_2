#ifndef ZONA_TUTORIAL_H
#define ZONA_TUTORIAL_H
#include "ZonaAccion.h"
class ZonaTutorial :
	public ZonaAccion
{
	TextoSDL texto_;

	void setTextos();
public:
	ZonaTutorial(Juego* j);
	virtual ~ZonaTutorial();

	virtual void draw();
};
#endif //ZONA_TUTORIAL_H
