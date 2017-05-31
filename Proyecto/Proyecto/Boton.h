#ifndef BOTON_H_
#define BOTON_H_

#include "Objeto.h"
#include "Juego.h"


class Boton : public Objeto
{
public:
	enum ButtonType
	{
		ILUMINADO,MECANICO,FUTURISTA,ILUMINADOBLANCO
	};
	
	typedef void CallBack_t(Juego* jg);
	Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons, string texto, string descripcion = "No hay descripcion");
	Boton(Juego* juego, string ID, SDL_Rect rect, CallBack_t * cbCons, string texto, string descripcion = "No hay descripcion");

	virtual ~Boton();
	virtual void draw();

	virtual void update();

	virtual void activo();

	virtual void normal();

	void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {};//Hay que ponerlo para que no sea bastracto
	void accion() { cb(pjuego); };
 	bool Dentro(int x, int y) {
		SDL_Point p = { x,y };
		return SDL_PointInRect(&p, &realRect)==SDL_TRUE;
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
	Juego::Animacion * Anim;
	Juego* pjuego;
	enum BUTTONSTATE_
	{
		NOT_SELECTED = 0, SELECTED = 1
	}BState_;
	double angulo;
	SDL_Rect realRect;
	
	TextoSDL Texto;
	int mpbx;
	int mpby;
	int _x, _y;
	string id;
	string nombre;
	string descripcion_;
};
class BotonMecanico:public Boton
{
public:
	BotonMecanico(Juego* juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion = "No hay descripcion");
	virtual ~BotonMecanico() {};
	virtual void update();

private:

};

class BotonFuturista :public Boton
{
public:
	BotonFuturista(Juego* juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion = "No hay descripcion");
	virtual ~BotonFuturista() {};
	virtual void update();

private:

};
class BotonIluminado :public Boton
{
public:
	BotonIluminado(Juego* juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion = "No hay descripcion");
	virtual ~BotonIluminado() {};
	virtual void update();

private:

};

class BotonIluminadoBlanco :public Boton
{
public:
	BotonIluminadoBlanco(Juego* juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion = "No hay descripcion");
	virtual ~BotonIluminadoBlanco() {};
	virtual void update();

private:

};

#endif