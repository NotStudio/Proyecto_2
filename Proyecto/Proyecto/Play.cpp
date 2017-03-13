#include "Play.h"
#include "checkML.h"

Play::Play(Juego * juego) : EstadoPG(juego)
{
	personaje = juego->getPlayer();
	zona = juego->getZona();

}


Play::~Play()
{

}

void Play::draw(){

	zona->draw();
	personaje->draw();
	
}

void Play::update(){

	personaje->update();
	
	zona->update();


}
