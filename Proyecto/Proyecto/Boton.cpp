#include "Boton.h"


Boton::Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons, string Nombre,string Descripcion )
{
	descripcion_ = Descripcion;
	angulo = 0;
	pjuego = juego;
	_x = x;
	_y = y;


	nombre = Nombre;

	rectb.x = x;
	rectb.y = y;

	rectb.h = 75;
	rectb.w = 200;
	
	realRect = rectb;

	activo.x = x - 25;
	activo.y = y - 12;
	activo.w = 250;
	activo.h = 100;

	
	id = ID;

	cb = cbCons;
	Texto.LoadFuente(pjuego->getTipografia("Acme____",16));
	Texto.loadTexto(pjuego->getRender(), nombre);

}


Boton::~Boton()
{
}

void Boton::draw(){
	pjuego->getTextura(id, "idle")->draw(pjuego->getRender(), realRect, nullptr,angulo);
	Texto.draw(pjuego->getRender(), realRect.x+(realRect.w- Texto.getAncho())/2, realRect.y+ (realRect.h - Texto.getAlto()) / 2);
}

void Boton::aumentar(){
	BState_ = BUTTONSTATE_::SELECTED;
	realRect = activo;
}
void Boton::normal(){
	BState_ = BUTTONSTATE_::NOT_SELECTED;
	realRect = rectb;
}
void Boton::update(){
	if (BState_) {
	}
	else {

	}

}


/*bool Boton::dentro(int x, int y) const{
	if (x >= pimgx && x <= pimgx + ancho && y >= pimgy && y <= pimgy + alto){
		return true;
	}
	return false;
}

	
*/