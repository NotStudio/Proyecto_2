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

	

public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Item(punteroJuego, spritePar, objectId) {
		
	}
	virtual ~Consumible() {
	};
	virtual void onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2) {
		if (dynamic_cast<Jugable*>(Contacto)) {
			effect();
			destruido = true;
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
		statsUp.vida = 10;
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
		statsUp.vidaMax = 10;
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
		statsUp.velMov = 20;
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
		statsUp.velAtq = -0.3;
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
		statsUp.daño = 5;
	}

	virtual void effect() {
		Consumible::effect();
	};
};

#endif