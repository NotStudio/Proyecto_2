#ifndef CAMBIO_H_
#define CAMBIO_H_
#include "EstadoPG.h"
#include "Boton.h"
#include "Room.h"



class Cambio : public  EstadoPG
{
public:
	Cambio(Juego * juego,int actual,int Personajes);
	~Cambio();
	int activo = 0;

private:
	int personajes;
	Room* pR;
	
	Boton*boton;

	static void resume(Juego * jg);
	static void returnMenu(Juego * jg);

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
	virtual void update();
	virtual void draw();
	void activar(Juego * jg){
		jg->setActivo(activo);
	}
};
#endif