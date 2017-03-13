#include "Enemigo.h"
#include "Bala.h"

Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : NPC(punteroJuego,spritePar,objectId)
{
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
void  Enemigo::update(){

	if (!destruido)
		Entidad::update();
	
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