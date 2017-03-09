#ifndef BOTON_H_
#define BOTON_H_

#include "Objeto.h"
#include "Juego.h"


class Boton : public Objeto
{
public:
	
	typedef void CallBack_t(Juego* jg);
	Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons);
	~Boton();
	void draw();
	//bool onClick();
	void update();


	//bool dentro(int x, int y) const;


protected:
	CallBack_t * cb;

	Juego* pjuego;

	SDL_Rect rectb;

	int mpbx;
	int mpby;

	string id;
};

#endif