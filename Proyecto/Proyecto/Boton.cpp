#include "Boton.h"


Boton::Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons, string Nombre)
{

	pjuego = juego;
	_x = x;
	_y = y;

	rectb.x = x;
	rectb.y = y;

	rectb.h = 75;
	rectb.w = 150;
	
	id = ID;

	cb = cbCons;
	Texto.LoadFuente(pjuego->getTipografia("lazy",20));
	Texto.loadTexto(pjuego->getRender(), Nombre);

}


Boton::~Boton()
{
}

void Boton::draw(){
	pjuego->getTextura(id, "idle")->draw(pjuego->getRender(), rectb, nullptr);
	Texto.draw(pjuego->getRender(), rectb.x+(rectb.w- Texto.getAncho())/2, rectb.y+ (rectb.h - Texto.getAlto()) / 2);
}

void Boton::aumentar(){
	rectb.y = _y - (100 - rectb.h)/2;
	rectb.x = _x - (200 - rectb.w) / 2;
	rectb.h = 100;
	rectb.w = 200;
}
void Boton::normal(){
	rectb.y = _y + (100 - rectb.h) / 2;
	rectb.x = _x + (200 - rectb.w) / 2;
	rectb.h = 75;
	rectb.w = 150;
}

/*bool Boton::onClick(){
	pjuego->getMousePos(mpbx, mpby);

	if (dentro(mpbx, mpby)){
		cb(pjuego);
		return true;
	}
	else
	{

		return false;
	}

}*/

void Boton::update(){

}


/*bool Boton::dentro(int x, int y) const{
	if (x >= pimgx && x <= pimgx + ancho && y >= pimgy && y <= pimgy + alto){
		return true;
	}
	return false;
}

	
*/