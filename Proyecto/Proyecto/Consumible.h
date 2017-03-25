#ifndef CONSUMIBLE_H_
#define CONSUMIBLE_H_
#include "Item.h"
#include "Jugable.h"
class Consumible :
	public Item
{
protected:
	virtual void effect(){
		
	
	};
	
	Personaje::atributos statsUp;
	float origPosY;
	const int diferenciaPos = 8;
	const float32 velLevitacion = 1.5f;

public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Item(punteroJuego, spritePar, objectId) {
		
		
		origPosY = sprite->y;
		body->SetLinearVelocity(b2Vec2{ 0,velLevitacion });

	}
	virtual ~Consumible() {
	};
	virtual void onColisionEnter(Objeto* Contacto) {
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
		BATERIA_COCHE = 10,
		CABLE = 20,
		BOOSTER = 21,
		TRANSISTOR = 30,
		PILA = 70
	};
};
//Pila: vida++
class Pila : public Consumible 
{

public:
	Pila(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Consumible(punteroJuego,spritePar,objectId){
		statsUp.daño = 0;
		statsUp.velAtq = 0;
		statsUp.velMov = 0;
		statsUp.vidaMax = 0;
		statsUp.vida = 1;
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
	
		static_cast<Jugable*>(pJuego->getPlayer())->applyEffect(statsUp);
	
	};
};

//Bateria: vida_max ++
class Bateria : public Consumible
{
	
public:
	Bateria(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		

	};
};
//Cable: velocidad de movimiento ++;
class Cable : public Consumible
{

	
public:

	Cable(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		

	};
};
//Transistor: velocidad de ataque ++
class Transistor : public Consumible
{
	
public:
	Transistor(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}

	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		

	};
};
//Booster: daño ++
class Booster : public Consumible
{
	
public:
	Booster(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {

	}

	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		

	};
};

#endif