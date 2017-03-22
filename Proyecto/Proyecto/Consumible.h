#ifndef CONSUMIBLE_H_
#define CONSUMIBLE_H_
#include "Item.h"
#include "Jugable.h"
class Consumible :
	public Item
{
protected:
	virtual void effect(){};
public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Item(punteroJuego, spritePar, objectId) {
		
		
	}
	virtual ~Consumible() {
	};
	virtual void onColisionEnter(Objeto* Contacto) {
		if (dynamic_cast<Jugable*>(Contacto)) {
			cout << " Tocado Consumible \n";
			destruido = true;
		}
	};

};
class Pila : public Consumible 
{
public:
	Pila(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Consumible(punteroJuego,spritePar,objectId){
		
	}
};
class Bateria : public Consumible
{
public:
	Bateria(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {}
};
class Cable : public Consumible
{
public:
	Cable(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {}
};
class Transistor : public Consumible
{
public:
	Transistor(Juego* punteroJuego, SDL_Rect spritePar, string objectId) :Consumible(punteroJuego, spritePar, objectId) {}
};

#endif