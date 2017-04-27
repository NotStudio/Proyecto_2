#include "Enemigo.h"
#include "Bala.h"
#include "BalaAmiga.h"
#include <cmath>
#include "Consumible.h"


Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia) : NPC(punteroJuego, spritePar, objectId), needDrop(false)
{
	_distancia = distancia;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	dropPool.push_back("Pila");
	dropPool.push_back("Bateria");
}


Enemigo::~Enemigo()
{
	
}

void Enemigo::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (contactObject != nullptr){
		//Si lo que ha colisionado con nosotros es una bala, comprobamos si es del jugador o de un enemigo
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){
			stats.vida -= static_cast<BalaAmiga*>(contactObject)->getDanyo();
			if (stats.vida <= 0) destruido = false;
		}
		//cambiar textura.
	}
}

void Enemigo::update(){
	if (!destruido){
		Entidad::update();
		comportamiento();
	}
	else {
		body->SetActive(false);
		if (needDrop) {
			dropItems();
			needDrop = false;
		}
	}
	
}
bool Enemigo::distancia() {
	float distancia = (pos -static_cast<Entidad*>(pJuego->getPlayer())->getBody()->GetPosition()).Length();
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
}

void Enemigo::dropItems() {
	int prob = rand() % 100;
	int numItemsDropped = 1;
	//Probabilidades de dropear algo.
	if (prob >= 50) {

		for (int i = 0; i < numItemsDropped; i++) {

			int probItem = rand() % 100;
			
			if (probItem < Consumible::BATERIA_COCHE) {
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Bateria(pJuego, SDL_Rect{ sprite->x +1,sprite->y +2,48,48 }, "Bateria"));
			}

			else if (probItem < Consumible::CABLE) {
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Cable(pJuego, SDL_Rect{ sprite->x - 2, sprite->y + 3, 48, 48 }, "Cable"));
			}
			else if (probItem < Consumible::BOOSTER) {
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Booster(pJuego, SDL_Rect{ sprite->x -5, sprite->y + 7, 48, 48 }, "Booster"));
			}
			else if (probItem < Consumible::TRANSISTOR) {
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Transistor(pJuego, SDL_Rect{ sprite->x, sprite->y, 48, 48 }, "Transistor"));
			}
			else if (probItem < Consumible::PILA) {
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Pila(pJuego, SDL_Rect{ sprite->x, sprite->y, 48, 48 }, "Pila"));
			}
		}
	}
}