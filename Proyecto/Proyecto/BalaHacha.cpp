#include "BalaHacha.h"


BalaHacha::BalaHacha(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) : BalaEnemiga(pJuego, spritePar, "BalaN", 10.0f, dirx, diry, 5)
{
	dirx_ = dirx;
	diry_ = diry;
}


BalaHacha::~BalaHacha()
{
}

void BalaHacha::update(){
	Bala::update();
}

void BalaHacha::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){

	if (rebotes = cont){
		destruido = true;
	}

	else{
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR)
			destruido = true;

		else if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO 
			|| b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO_NOCOL){//mirar porque no cambia de dirreccion
		
			/******************
			*
			*
			*
			*
			hacer aqui que cambie la direccion y darsela
			*
			*
			*
			********************/
			rebotes++;
		}
	}
}