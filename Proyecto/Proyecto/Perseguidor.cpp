#include "Perseguidor.h"
#include "checkML.h"
#include "Bala.h"



//HAY QUE CAMBIAR EL STRING QUE PASA COMO ID
Perseguidor::Perseguidor(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, {x,y,64,57}, "Iman", 300), coefMov(20.0f)
{
	for (unordered_map<string,Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones.at(i->first)->setNumFrames(30);
	}
	currentAnim = animaciones.at("walk");
	stats.daño = 1;
	stats.vida = 5;

	
}
void Perseguidor::move(){
	if (distancia()){
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

		velFloat.x = unitario.x*coefMov;
		velFloat.y = unitario.y*coefMov;

		body->SetLinearVelocity(velFloat);
		currentAnim->ActualizarFrame();
	}
	else
	{
		stop();
	}
}
void Perseguidor::update() {
	Enemigo::update();
	
}

void Perseguidor::tellBody(b2Body* b){
	b2 = b;
}

void Perseguidor::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {

	if (contactObject != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){
			stats.vida--;
			if (stats.vida <= 0){
				Enemigo::onColisionEnter(contactObject, b1, b2);
				needDrop = true;
			}
		}
	}
}

Perseguidor::~Perseguidor()
{
}

void Perseguidor::dropItems(){
	Enemigo::dropItems();
	
}

void Perseguidor::comportamiento() {
	move();
}