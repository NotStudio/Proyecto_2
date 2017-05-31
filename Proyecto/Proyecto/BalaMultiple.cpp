#include "BalaMultiple.h"


BalaMultiple::BalaMultiple(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) :BalaEnemiga(pJuego, spritePar, "hacha", 7, dirx, diry, 15)
{
	distViajada = 0;
	distMax = 400;
	origen = b2Vec2(spritePar.x / PPM, spritePar.y / PPM);
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones.at(i->first)->setNumFrames(30);
	}
	currentAnim = animaciones.at("move");

}


BalaMultiple::~BalaMultiple()
{
}



void BalaMultiple::dividir() {
	
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 5, 1, 0, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 5, -1, 0, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 5, 0, 1, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 5, 0, -1, 5));
	
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 10, 1, 1, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 10, -1, 1, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 10, 1, -1, 5));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "hachasola", 10, -1, -1, 5));

}

void BalaMultiple::update(){
	Bala::update();

	currentAnim->ActualizarFrame();

		aux1 = (origen.x - pos.x) * PPM;
		aux2 = (origen.y - pos.y) * PPM;
		distViajada = sqrt(pow(aux1, 2) + pow(aux2, 2));

		if (choque)
			destruido = true;

		if (distViajada > distMax){
			destruido = true;
			dividir();
		}
}

void BalaMultiple::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {

	choque = true;

}

