#ifndef CRAFTEO_H
#define CRAFTEO_H
#include "EstadoPG.h"
#include "MenuJuego.h"
class Crafteo :
	public MenuJuego
{
protected:
	static void salir(Juego * jg);
	static void grado1(Juego* jg);
	static void grado2(Juego* jg);
	static void grado3(Juego* jg);
	

public:
	Crafteo(Juego* juego);
	virtual ~Crafteo();


};

#endif