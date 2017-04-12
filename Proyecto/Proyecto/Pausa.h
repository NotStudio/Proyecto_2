#ifndef PAUSA_H_
#define PAUSA_H_
#include "EstadoPG.h"
#include "Boton.h"
#include "Room.h"



class Pausa : public  EstadoPG
{
public:
	Pausa(Juego * juego);
	~Pausa();

private:

	Room* pR;
	int activo = 0;
	std::vector <Boton*> botones;

	static void resume(Juego * jg);
	static void returnMenu(Juego * jg);

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
	virtual void update();
	virtual void draw();
};
#endif