#ifndef CRAFTEO_H
#define CRAFTEO_H
#include "EstadoPG.h"
#include "Boton.h"
class Crafteo :
	public EstadoPG
{

	std::vector <Boton*> botones;

	int activo = 0;
	static int seleccion;
	static void salir(Juego * jg);
	static void grado1(Juego* jg);
	static void grado2(Juego* jg);
	static void grado3(Juego* jg);


	

public:
	Crafteo(Juego* juego);
	virtual ~Crafteo();
	virtual void update();
	virtual void draw();
};

#endif