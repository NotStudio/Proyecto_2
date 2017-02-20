#pragma once
#include <Box2D\Box2D.h>
#include <SDL.h>
#include "Codigo\Objeto.h"
#include "Codigo\Juego.h"
class Entidad :	public Objeto
{
protected:

	b2Vec2 pos; //Posicion del objeto.
	SDL_Rect sprite;//Posicion (que es la misma de arriba) y tamaño del objeto.
	Juego::Texturas_t texturaEnum; //Enumerado de la textura. *Temporal*
	//Atributos de Box2D
	b2Shape* shape;
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fDef;
	//Struct de animacion.
	std::vector<Juego::Animacion> animaciones;
	
	
public:

	Entidad();

	virtual ~Entidad();

	//virtual void draw();

};

