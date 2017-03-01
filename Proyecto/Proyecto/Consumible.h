#pragma once
#include "Item.h"
#include "Jugable.h"
class Consumible :
	public Item
{
public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Item(punteroJuego, spritePar, objectId) {
		body = pJuego->getWorld()->CreateBody(&bodyDef);
		body->SetUserData(this);
		bodyDef.position.Set((float32)sprite.x, (float32)sprite.y);
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite.w / 2, sprite.h / 2);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 1.0f;
		body->CreateFixture(&fDef);
	}
	~Consumible() {};
	virtual void onColisionEnter(Objeto* Contacto) {
		if (dynamic_cast<Jugable*>(Contacto)) 
			cout<< " Tocado Consumible \n";
	};
};
class Pila : public Consumible 
{
public:
	Pila(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Consumible(punteroJuego,spritePar,objectId){}
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