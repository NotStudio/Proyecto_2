#include "EstadoPG.h"


EstadoPG::EstadoPG(Juego * juego)
{
	ptsjuego = juego;

}


EstadoPG::~EstadoPG()
{
}

void EstadoPG::draw(){
	for (int i = 0; i < objetos.size(); i++){
		objetos[i]->draw();
	
}


/*void EstadoPG::onClick(){ //Este metodo sera solo para los botones de los menus
	bool clickeado = false; //igual que en juegoPG

	int i = objetos.size() - 1;
	while (!clickeado && i >= 0)
	{
		if (objetos[i]->onClick())
			clickeado = true;

		i--;
	}*/

}


void EstadoPG::update(){
	for (int i = 0; i < objetos.size(); i++){
		objetos[i]->update();
	}

}