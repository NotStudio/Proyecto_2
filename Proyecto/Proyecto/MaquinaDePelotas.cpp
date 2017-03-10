#ifndef PERSEGUIDOR_H_
#define PERSEGUIDOR_H_
#ifndef Enemigo_h_
#define Enemigo_h_
#endif
#include "MaquinaDePelotas.h"
#include "EstadoPG.h"
#include "Bala.h"


MaquinaDePelotas::MaquinaDePelotas(Juego* punteroJuego, SDL_Rect a) : Enemigo(punteroJuego, a, "Tostadora")
{
}


MaquinaDePelotas::~MaquinaDePelotas()
{
}
void MaquinaDePelotas::update(){
	Entidad::update();
	move();
}
void MaquinaDePelotas::onColisionEnter(Objeto* contactObject) {

	//cout << "Se ha usted chocado con la maquina de pelotas decidan que pasa diseñadores";
}
void MaquinaDePelotas::move(){
	
	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;

	b2Vec2 posJug = b2Vec2(x, y);
	//Vector para la diferencia entre el vect del jugador y el vect del enemigoPerseguidor
	b2Vec2 vecDir = posJug - pos;

	//Calculamos el vector unitario del vector de direccion.
	b2Vec2 unitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

	velFloat.x = unitario.x;
	velFloat.y = unitario.y;
	SDL_Rect posicion;
	posicion.x = pos.x + sprite->w / 2;
	posicion.y = pos.y + sprite->h / 2;
	posicion.w = 10;
	posicion.h = 10;

	posicion.x += velFloat.x * 35;
	posicion.y += velFloat.y * 35;
	Uint32 lastUpdate = SDL_GetTicks();
//	cout << contador;
	if (lastUpdate - contador > cadencia){
		 //contador++;
	contador = SDL_GetTicks();
	//cout << " Velx " << velFloat.x << " Vely  " << velFloat.y;
	dynamic_cast<EstadoPG*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, velFloat.x, velFloat.y));
	}
}
#endif