#include "Perseguidor.h"
#include "checkML.h"
#include "Bala.h"
#include "Consumible.h"


//HAY QUE CAMBIAR EL STRING QUE PASA COMO ID
Perseguidor::Perseguidor(Juego* punteroJuego, SDL_Rect a) : Enemigo(punteroJuego, a, "Iman",300), coefMov(10.0f)
{
	stats.daño = 1;
	stats.vida = 5;

	dropPool.push_back("Pila");
	dropPool.push_back("Bateria");
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
	}
	else
	{
		stop();
	}
}
void Perseguidor::update() {
	Entidad::update();
	move();
	if (needDrop) {
		dropItems();
		needDrop = false;
	}
	
	
}
void Perseguidor::onColisionEnter(Objeto* contactObject) {



	if (contactObject != nullptr) {
		if (dynamic_cast<Bala*>(contactObject)) {
			stats.vida--;
			if (stats.vida <= 0){
				Enemigo::onColisionEnter(contactObject);
				needDrop = true;
			}
				
		}
	}
}

Perseguidor::~Perseguidor()
{
}

void Perseguidor::dropItems(){

	 int prob = rand() % 100;
	 int numItemsDropped;
	 //Segun 'prob', el enemigo dropea 1 o 2 objetos. Tal vez esté muy cheto.
	 if (prob > 80)
		 numItemsDropped = 2;
	 else numItemsDropped = 1;
	

	for (int i = 0; i < numItemsDropped; i++){

		string item = dropPool[rand() % 1];

		if (item == "Pila"){
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Pila(pJuego, SDL_Rect{sprite->x,sprite->y,64,64},"Pila"));
		}

		else if (item == "Bateria"){
			//dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new Bateria(pJuego, SDL_Rect{ sprite->x, sprite->y, 64, 64 }, "Bateria"));
		}

	}


}