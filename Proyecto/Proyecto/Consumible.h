#ifndef CONSUMIBLE_H_
#define CONSUMIBLE_H_
#include "Item.h"
#include "Jugable.h"
class Consumible :
	public Item
{
protected:
	//Le sumamos a los stats del personaje los stats del consumible.
	virtual void effect(){
		static_cast<Jugable*>(pJuego->getPlayer())->applyEffect(statsUp);
	};
	
	Personaje::atributos statsUp;
	float origPosY;
	const int diferenciaPos = 8;
	const float32 velLevitacion = 0.05f;

public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Item(punteroJuego, spritePar, objectId) {
		
		origPosY = sprite->y;
		body->SetLinearVelocity(b2Vec2{ 0,velLevitacion });

	}
	virtual ~Consumible() {
	};
	virtual void onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2) {
		if (dynamic_cast<Jugable*>(Contacto)) {
			effect();
			cout << " Tocado "<< id << " \n";
			destruido = true;
		}
	};

	virtual void update() {

		Item::update();
		levitar();
	};

	void levitar() {
	
		if (sprite->y >= origPosY + diferenciaPos) {
			body->SetLinearVelocity(b2Vec2{ 0,-velLevitacion });
		}
		else if (sprite->y <= origPosY - diferenciaPos) {
			body->SetLinearVelocity(b2Vec2{ 0,velLevitacion });
		}
	};
	enum PROBABILIDAD {
		BATERIA_COCHE = 5, //5% de poisibilidad
		CABLE = 20,		   //15% de posibilidad
		BOOSTER = 40,	   //20% de posibilidad
		TRANSISTOR = 60,   //20% de posibilidad
		PILA = 100		   //40% de posibilidad
	};
};
//Pila: vida++
class Pila : public Consumible 
{

public:
	Pila(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Consumible(punteroJuego,spritePar,objectId){
		statsUp.vida = 1;
	}
	virtual void effect() {
		Consumible::effect();
	};
};

//Bateria: vida_max ++
class Bateria : public Consumible
{
public:
	Bateria(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		statsUp.vidaMax = 1;
	}
	virtual void effect() {
		Consumible::effect();
	};
};
//Cable: velocidad de movimiento ++;
class Cable : public Consumible
{
public:
	Cable(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		statsUp.velMov = 10;
	}
	virtual void effect() {
		Consumible::effect();
	};
};
//Transistor: velocidad de ataque ++
class Transistor : public Consumible
{
public:
	Transistor(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		statsUp.velAtq = 10;
	}

	virtual void effect() {
		Consumible::effect();
	};
};
//Booster: daño ++
class Booster : public Consumible
{
public:
	Booster(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		statsUp.daño = 10;
	}

	virtual void effect() {
		Consumible::effect();
	};
};

#endif