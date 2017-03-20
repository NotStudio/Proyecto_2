#include "Boton.h"


Boton::Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons)
{
	pjuego = juego;

	rectb.x = x;
	rectb.y = y;

	rectb.h = 100;
	rectb.w = 200;

	id = ID;

	cb = cbCons;
}


Boton::~Boton()
{
}

void Boton::draw(){

	pjuego->getTextura(id, "idle")->draw(pjuego->getRender(), rectb, nullptr);

}

void Boton::aumentar(){
	rectb.h = 130;
	rectb.w = 250;
}
void Boton::normal(){
	rectb.h = 100;
	rectb.w = 200;
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