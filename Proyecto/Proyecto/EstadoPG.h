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
	virtual void handleEvent(const SDL_Event& event) {};
	virtual void fixedUpdate(){};
	vector<Objeto*> extras;//Objetos en el momento de creacion solo tenia balas
protected:

	Juego*pJuego;
	
	std::vector <Objeto*> objetos;  
     SDL_TimerID timer;
    Uint32 cadencia = 500;
	Uint32 timerUpdate(Uint32 intervalo) {
			 fixedUpdate();
			 return 0;
		 }

};

#endif