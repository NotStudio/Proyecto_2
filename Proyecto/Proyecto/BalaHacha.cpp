#include "BalaHacha.h"


BalaHacha::BalaHacha(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) :Bala(pJuego, spritePar, "BalaA", 1.0f, dirx, diry, 1)
{
	dirx_ = dirx;
	diry_ = diry;
}


BalaHacha::~BalaHacha()
{
}

void BalaHacha::update(){
	Entidad::update();
}

void BalaHacha::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){

	if (rebotes = cont){
		destruido = true;
	}

	else{
		if (b2->GetFixtureList()->GetFilterData().maskBits == Juego::JUGADOR)
			destruido = true;

		else{
			int rnd = rand() % 2;
			if (rnd == 0)
				dirx_ = -dirx_;
			if (rnd == 1)
				diry_ = -diry_;
			rebotes++;
		}
	}
}