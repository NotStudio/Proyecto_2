#include "TrampaElectrica.h"

uint32 changeActiveCb(Uint32 intervalo, void * param) {
	static_cast<TrampaElectrica*>(param)->changeState();

	return 0;
}


TrampaElectrica::TrampaElectrica(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x,y,64,64 }, "Iman", 300), activated(true), needChange(true)
{
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO;
	fDef.isSensor = true;
	body->CreateFixture(&fDef);


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
		SDL_AddTimer(3000, changeActiveCb, this);
		needChange = false;
	}
}
