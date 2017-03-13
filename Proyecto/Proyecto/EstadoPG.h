#ifndef ESTADO_H_
#define ESTADO_H_

#include "EstadoJuego.h"
#include "Juego.h"
#include "Objeto.h"

class EstadoPG :
	public EstadoJuego
{
public:
	EstadoPG(Juego * juego);
	virtual ~EstadoPG();

	virtual void draw();
	virtual void update();
	vector<Objeto*> extras;//Objetos en el momento de creacion solo tenia balas
protected:

	Juego* ptsjuego;
	
	std::vector <Objeto*> objetos;  

};

#endif