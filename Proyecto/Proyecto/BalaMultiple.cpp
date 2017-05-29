#include "BalaMultiple.h"


BalaMultiple::BalaMultiple(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) :BalaEnemiga(pJuego, spritePar, "BalaN", 5, dirx, diry, 10)
{
	distViajada = 0;
	distMax = 400;
	origen = b2Vec2(spritePar.x / PPM, spritePar.y / PPM);


}


BalaMultiple::~BalaMultiple()
{
}



void BalaMultiple::dividir() {
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "BalaN", 10, 1, 1, 1));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "BalaN", 10, -1, 1, 1));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "BalaN", 10, 1, -1, 1));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, { pos.x * PPM, pos.y* PPM, 32, 32 }, "BalaN", 10, -1, -1, 1));

}

void BalaMultiple::update(){
	Bala::update();

	
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

