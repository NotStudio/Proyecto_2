#ifndef CONSUMIBLE_H_
#define CONSUMIBLE_H_
#include "Item.h"
#include "Jugable.h"
class Consumible :
	public Item
{
protected:
	virtual void effect(){
		//Recogemos los stats del jugador.
		stats = static_cast<Jugable*>(pJuego->getPlayer())->getStats();
		statsMax = static_cast<Jugable*>(pJuego->getPlayer())->getStatsMax();
	};
	Personaje::atributos* stats;
	const Personaje::atributos* statsMax;
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
	const int vidaUp = 1;

public:
	Pila(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Consumible(punteroJuego,spritePar,objectId){
		
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		if (stats->vida + vidaUp <= stats->vidaMax);
		stats->vida += vidaUp;
	
	};
};

//Bateria: vida_max ++
class Bateria : public Consumible
{
	const int vidaMaxUp = 1;
public:
	Bateria(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		if (stats->vidaMax + vidaMaxUp <= statsMax->vidaMax)
			stats->vidaMax += vidaMaxUp;

	};
};
//Cable: velocidad de movimiento ++;
class Cable : public Consumible
{

	const int velMovUp = 10;
public:

	Cable(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}
	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		if (stats->velMov + velMovUp <= statsMax->velMov)
			stats->velMov += velMovUp;

	};
};
//Transistor: velocidad de ataque ++
class Transistor : public Consumible
{
	const int velAtUp = 1;
public:
	Transistor(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {
		
	}

	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		if (stats->velAtq + velAtUp <= statsMax->velAtq)
			stats->velAtq += velAtUp;

	};
};
//Booster: daño ++
class Booster : public Consumible
{
	const int dañoUp = 1;
public:
	Booster(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {

	}

	virtual void effect() {
		Consumible::effect();
		//Añadimos el efecto.
		if (stats->daño + dañoUp <= statsMax->daño)
			stats->daño += dañoUp;

	};
};

#endif