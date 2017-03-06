#include "Play.h"


Play::Play(Juego * juego) : EstadoPG(juego)
{
	personaje = juego->getPlayer();
}


Play::~Play()
{

}

void Play::draw(){

	EstadoPG::draw();

	personaje->draw();

	for (int i = 0; i < enemigos.size(); i++){
		enemigos[i]->draw();

	}
}

void Play::update(){

	EstadoPG::update();

	personaje->update();

	for (int i = 0; i < enemigos.size(); i++){
		enemigos[i]->update();

	}
}
