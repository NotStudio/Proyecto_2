#pragma once
#include "EstadoPG.h"
//#include "Boton.h"

class Pausa : public  EstadoPG
{
public:
	Pausa(Juego * juego);
	~Pausa();

private:
	static void resume(Juego * jg);
	static void menu(Juego * jg);
};
