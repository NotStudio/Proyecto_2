#ifndef PAUSA_H_
#define PAUSA_H_
#include "EstadoPG.h"
#include "Boton.h"
#include "Room.h"
#include "MenuJuego.h"



class Pausa : public  MenuJuego
{
public:
	Pausa(Juego * juego);
	~Pausa();

private:
	static void resume(Juego * jg);
	static void returnMenu(Juego * jg);
	static void opciones(Juego * jg);
	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
};
#endif