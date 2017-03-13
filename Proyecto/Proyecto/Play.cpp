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
	for (int i = 0; i < extras.size(); i++) {
		extras[i]->draw();
	}
}

void Play::update(){

	personaje->update();
	for (int i = 0; i < extras.size(); i++) {
		if (extras[i] != nullptr)
		if (!extras[i]->getdestruido())
			extras[i]->update();
		else {
			delete extras[i];
			extras[i] = nullptr;
		}
	}
	for (int i = 0; i < extras.size(); i++) {
		if (extras[i] == nullptr)	{
			extras.erase(extras.begin() + i);
			i--;
		}
	}
	zona->update();


}
