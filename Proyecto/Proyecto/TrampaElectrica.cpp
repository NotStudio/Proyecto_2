#include "TrampaElectrica.h"

uint32 changeActiveCb(Uint32 intervalo, void * param) {
	static_cast<TrampaElectrica*>(param)->changeState();

	return 0;
}


TrampaElectrica::TrampaElectrica(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x,y,128,128 }, "Iman", 300), activated(true), needChange(true)
{
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO;
	fDef.isSensor = true;
	body->CreateFixture(&fDef);
	isKillable = false;
	stats.velAtq = 2;
	stats.daño = 5;
	cadencia = stats.velAtq * 1000;
	sprite->h = 32;
	sprite->w = 32;

}


TrampaElectrica::~TrampaElectrica()
{
	
}

void TrampaElectrica::onColisionEnter(Objeto * contactObject, b2Body * b1, b2Body * b2)
{
	if (b2 != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR) {
			if (activated) {

				std::cout << "haciendo daño \n";
			}
		}
	}
}


void TrampaElectrica::comportamiento()
{
	alternaActivo();
}

void TrampaElectrica::alternaActivo() {

	if (needChange) {
		SDL_AddTimer(cadencia, changeActiveCb, this);
		needChange = false;
	}
}
