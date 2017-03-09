#ifndef PAUSA_H_
#define PAUSA_H_
#include "EstadoPG.h"



class Pausa : public  EstadoPG
{
public:
	Pausa(Juego * juego);
	~Pausa();

private:
	static void resume(Juego * jg);
	static void base(Juego * jg);
};
#endif