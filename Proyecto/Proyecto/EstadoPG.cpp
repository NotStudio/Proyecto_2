#include "EstadoPG.h"
#include "checkML.h"

EstadoPG::EstadoPG(Juego * juego)
{
	pJuego = juego;

}


EstadoPG::~EstadoPG()
{
}

void EstadoPG::draw(){
	for (int i = 0; i < objetos.size(); i++){
		objetos[i]->draw();
	
	}
}


void EstadoPG::update(){
	for (int i = 0; i < objetos.size(); i++){
		objetos[i]->update();
	}

}