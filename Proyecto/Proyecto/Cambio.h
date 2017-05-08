#ifndef CAMBIO_H_
#define CAMBIO_H_
#include "MenuJuego.h"
#include "Boton.h"
#include "Room.h"
#include <vector>



class Cambio : public  MenuJuego
{
public:
	Cambio(Juego * juego,vector<Objeto*>&personjes);
	~Cambio();


private:
	static void resume(Juego * jg);
	static void returnMenu(Juego * jg);

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
};
#endif