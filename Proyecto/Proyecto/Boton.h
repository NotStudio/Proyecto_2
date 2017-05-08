#ifndef BOTON_H_
#define BOTON_H_

#include "Objeto.h"
#include "Juego.h"


class Boton : public Objeto
{
public:
	
	typedef void CallBack_t(Juego* jg);
	Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons, string, string descripcion = "No hay descripcion");
	~Boton();
	void draw();

	void update();

	void aumentar();

	void normal();

	void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {};//Hay que ponerlo para que no sea bastracto
	void accion() { cb(pjuego); };
 	bool Dentro(int x, int y) {
		SDL_Point p = { x,y };
		return SDL_PointInRect(&p, &rectb)==SDL_TRUE;
	}

	std::string getNombre(){

		return nombre;
	}
	string getDescripcion() {
		return descripcion_;
	}
	virtual SDL_Rect * getRect(){ return &realRect; }

protected:
	CallBack_t * cb;

	Juego* pjuego;
	enum BUTTONSTATE_
	{
		NOT_SELECTED = 0, SELECTED = 1
	}BState_;
	double angulo;
	SDL_Rect realRect;
	SDL_Rect rectb;
	SDL_Rect activo;
	TextoSDL Texto;
	int mpbx;
	int mpby;
	int _x, _y;
	string id;
	string nombre;
	string descripcion_;
};

#endif