#ifndef ZONA_BASE_H_
#define ZONA_BASE_H_

#include "ZonaJuego.h"
class ZonaBase :
	public ZonaJuego
{

	Room* baseNivel;
public:
	ZonaBase(Juego* punteroJuego);
	virtual ~ZonaBase();
	virtual void draw();
	virtual void update();
	virtual SDL_Rect getNivelActual();

	void setTextos();
	void updateTextos();

	TextoSDL texto1_;
	TextoSDL texto2_;
	TextoSDL texto3_;
	string frase1_, frase2_, frase3_;
	float timerTexto_;

	bool personaje = false;
	bool misiones = false;
	bool materiales = false;
	bool historia = false;
	bool nave = false;

};

#endif