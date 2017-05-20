#ifndef PERSEGUIDOR_H_
#define PERSEGUIDOR_H_
#ifndef Enemigo_h_
#define Enemigo_h_
#endif
#include "MaquinaDePelotas.h"
#include "EstadoPG.h"
#include "Bala.h"
#include "ZonaAccion.h"
#include "BalaEnemiga.h"
#include "BalaAmiga.h"

MaquinaDePelotas::MaquinaDePelotas(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, {x,y,128,128}, "Tornillero", 500)
{

	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->CreateFixture(&fDef);
	body->SetType(b2_staticBody);
	stats.daño = 10;
	stats.vida = 40;
	stats.velMov = 0;
	stats.velAtq = 1.4;
	isKillable = true;
	cadencia = stats.velAtq * 1000;


}


MaquinaDePelotas::~MaquinaDePelotas()
{
	
}

void MaquinaDePelotas::comportamiento(){
	ataque();
}


void MaquinaDePelotas::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){

	if (contactObject != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){
			stats.vida -= static_cast<BalaAmiga*>(contactObject)->getDanyo();
			if (stats.vida <= 0){
				muerte();
			}
		}
	}

}
void MaquinaDePelotas::ataque(){

	if (!destruido) {

		if (Enemigo::distancia()) {

			float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
			float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
			b2Vec2 velFloat;
			velFloat.x = 0.0f;
			velFloat.y = 0.0f;

			b2Vec2 posJug = b2Vec2(x / PPM, y / PPM);
			//Vector para la diferencia entre el vect del jugador y el vect del enemigoPerseguidor
			b2Vec2 vecDir = posJug - pos;

			//Calculamos el vector unitario del vector de direccion.
			b2Vec2 unitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

			velFloat.x = unitario.x;
			velFloat.y = unitario.y;
			SDL_Rect posicion;
			posicion.x = pos.x * PPM + sprite->w / 2;
			posicion.y = pos.y * PPM + sprite->h / 5;
			posicion.w = 30;
			posicion.h = 30;

			posicion.x += velFloat.x * 70;
			posicion.y += velFloat.y * 70;
			Uint32 lastUpdate = SDL_GetTicks();
			//	cout << contador;
			if (lastUpdate - contador > cadencia) {
				//contador++;
				contador = SDL_GetTicks();
				//cout << " Velx " << velFloat.x << " Vely  " << velFloat.y;
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, "BallTBala", 43.0f, velFloat.x, velFloat.y, stats.daño));
			}
		}
	}
}
#endif