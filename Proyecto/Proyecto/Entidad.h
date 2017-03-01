#pragma once
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "Objeto.h"
#include "Juego.h"

class Entidad :	public Objeto
{
protected:
	Juego* pJuego; //Puntero al juego
	b2Vec2 pos; //Posicion del objeto.
	b2Vec2 vel; //Velocidad del objeto.
	SDL_Rect sprite;//Posicion (que es la misma de arriba) y tamaño del objeto.
	//Atributos de Box2D
	b2Shape* shape;
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fDef;
	//Struct de animacion.
	std::vector<Juego::Animacion> animaciones;
	Juego::Animacion currentAnim;
	//Nombre entidad
	string id;
	//Gestor de animaciones.
	 //virtual void updateAnim();
	
public:

	Entidad(Juego* punteroJuego, SDL_Rect spritePar , string objectId);

	virtual ~Entidad();

	virtual void draw();

	virtual void update();

	b2Body* getBody();

	std::string getId() { return id; };
	int getX(){
		return pos.x;

	}
	int getY(){
		return pos.y;

	}


	

	
	

};

