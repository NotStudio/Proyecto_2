#include "Enemigo.h"
#include "Bala.h"
#include <cmath>

Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia) : NPC(punteroJuego, spritePar, objectId)
{
	_distancia = distancia;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO;
	body->CreateFixture(&fDef);

}


Enemigo::~Enemigo()
{
	delete shape;
	shape = nullptr;
}

void Enemigo::onColisionEnter(Objeto* contactObject) {

	//Si lo que ha colisionado con nosotros es una bala, comprobamos si es del jugador o de un enemigo
	if (dynamic_cast<Bala*>(contactObject)){
		if (static_cast<Bala*>(contactObject)->getLanzador() == 0){
			destruido = true;
		}
		//cambiar textura.

	}

}
void Enemigo::update(){
	if (!destruido){
		Entidad::update();


	}
}
	bool Enemigo::distancia(){
	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();

		float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
		float distancia = sqrt((x - pos.x)*(x - pos.x) + (y - pos.y)*(y - pos.y));
		cout << distancia << " "<< _distancia<<"\n";
		if (distancia < _distancia) return true;
		else return false;
	}
void Enemigo::stop() {
	body->SetLinearVelocity(b2Vec2{ 0,0 });
}

void Enemigo::draw(){
	if (!destruido){
		Entidad::draw();
	}
	else{
		body->SetActive(false);
	}
}