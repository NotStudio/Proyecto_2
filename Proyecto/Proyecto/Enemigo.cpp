#include "Enemigo.h"
#include "BalaAmiga.h"
#include <cmath>
#include "Consumible.h"
#include "ObjetoHistorico.h"



Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int distancia) : NPC(punteroJuego, spritePar, objectId), needDrop(false), isDead_(false)
{
	_distancia = distancia;


	dropPool.push_back("Carbon");
	dropPool.push_back("Madera");
	dropPool.push_back("Chatarra");
	dropPool.push_back("Engranaje");
	dropPool.push_back("Tuercas");
	dropPool.push_back("Tuberias");
	dropPool.push_back("Fusible");
	dropPool.push_back("Estanyo");
	dropPool.push_back("Chip");
	dropPool.push_back("Sensor");
	dropPool.push_back("Litio");
}


Enemigo::~Enemigo()
{
	
}

void Enemigo::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (contactObject != nullptr){
		//Si lo que ha colisionado con nosotros es una bala, comprobamos si es del jugador o de un enemigo
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){
			stats.vida -= static_cast<BalaAmiga*>(contactObject)->getDanyo();
			if (stats.vida <= 0)
				muerte();

		}
		//cambiar textura.
	}
}

void Enemigo::update(){
	
	if (!isDead_){
		Entidad::update();
		comportamiento();
	}
	else {
		if(body->IsActive())
			body->SetActive(false);
		if (noDeadAnim){
			desactivar();
		}
		else {
			nextFrame();
			if (currentAnim->animacionAcabada()){
				desactivar();
			}
		}
	}
}

void Enemigo::desactivar(){
	if (isDead_) {
		destruido = true;
		if (needDrop) {
			dropItems();
			needDrop = false;
		}
		isDead_ = false;
	}
}

void Enemigo::muerte(){
	isDead_ = true;
	needDrop = true;
	try{
		currentAnim = animaciones.at("dead");
	}
	catch (...)// Esto es que pilla todas las expeciones
	{
		noDeadAnim = true;
	}
}
bool Enemigo::distancia() {
	float distancia = (pos - static_cast<Entidad*>(pJuego->getPlayer())->getBody()->GetPosition()).Length() * PPM;
	if (distancia < _distancia) return true;
	else return false;
}
void Enemigo::stop() {
	body->SetLinearVelocity(b2Vec2{ 0,0 });
}

void Enemigo::draw(){
	if (!destruido || isDead_){
		Entidad::draw();
	}
}

void Enemigo::dropItems() {

	//30% de spawnear ALGO
	int probSpawnSomething = rand() % 100;
	if (probSpawnSomething < 30) {
		//50% de spawnear item u objeto clave

		int probSpawnItem = rand() % 100; //si probSpawnItem < 50 ---> spawn item. Else, spawn objetoclave
		int numItemsDropped = 1;
		
		if (probSpawnItem < 50) {

			for (int i = 0; i < numItemsDropped; i++) {

				int probItem = rand() % 100;

				if (probItem < Consumible::BATERIA_COCHE) {
					dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Bateria(pJuego, SDL_Rect{ sprite->x + 1,sprite->y + 2,48,48 }, "BateriaCoche"));
				}

				else if (probItem < Consumible::CABLE) {
					dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Cable(pJuego, SDL_Rect{ sprite->x - 2, sprite->y + 3, 48, 48 }, "Cable"));
				}
				else if (probItem < Consumible::BOOSTER) {
					dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Booster(pJuego, SDL_Rect{ sprite->x - 5, sprite->y + 7, 48, 48 }, "Booster"));
				}
				else if (probItem < Consumible::TRANSISTOR) {
					dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Transistor(pJuego, SDL_Rect{ sprite->x, sprite->y, 48, 48 }, "Transistor"));
				}
				else if (probItem < Consumible::PILA) {
					dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Pila(pJuego, SDL_Rect{ sprite->x, sprite->y, 48, 48 }, "Pila"));
				}
			}
		}
		//Spawn objetoClave
		else {

			for (int i = 0; i < numItemsDropped; i++) {
				int x; int y;
				int pos = rand() % 2;
				if (pos == 0) pos = -1;
				x = rand() % 10 * pos;
				y = rand() % 10 * (pos * -1);
				int cantidad = rand() % 5;
				int objeto = rand() % dropPool.size();
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new ObjetoHistorico(pJuego, {sprite->x + x,sprite->y + y,64,64},dropPool[objeto],cantidad));
			
			}
		}
	}
}