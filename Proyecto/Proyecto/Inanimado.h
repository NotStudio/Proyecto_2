#ifndef INANIMADO_H_
#define INANIMADO_H_



#include "Entidad.h"

class Inanimado :
	public Entidad
{
public:
	Inanimado(Juego * pj, SDL_Rect Tam, string id): Entidad(pj,Tam,id){
		bodyDef.type = b2_staticBody;
		bodyDef.fixedRotation = true;
		bodyDef.position.Set(pos.x, pos.y);
		body = pJuego->getWorld()->CreateBody(&bodyDef);
		body->SetUserData(this);
		if (id == "agujero") {
			shape = new b2CircleShape();
			static_cast<b2CircleShape*>(shape)->m_p = {(float32)sprite->w / 2,(float32)sprite->h / 2 };
			static_cast<b2CircleShape*>(shape)->m_radius= Tam.w/2;
		}
		else {
			shape = new b2PolygonShape;
			static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		}
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		
	}
	virtual ~Inanimado() {
		delete shape; shape = nullptr;
	};
	virtual void onColisionEnter(Objeto * o = nullptr) {};
};

//==============================================================================================
//AGUJERO
class Agujero:
	public Inanimado
{
public:
	Agujero(Juego * Pj, SDL_Point Pos, float tam) :Inanimado(Pj, SDL_Rect{Pos.x,Pos.y,TILE_WIDTH*tam,TILE_HEIGHT*tam}, "agujero") {
	
		fDef.filter.categoryBits = Juego::ESCENARIO_NOCOL;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO;
		body->CreateFixture(&fDef);	
	}
	~Agujero() { };
private:

};
//==============================================================================================
//TUBERIA
class Tuberia: public Inanimado
{
public:
	Tuberia(Juego * Pj, SDL_Point Pos, int tam) :Inanimado(Pj, SDL_Rect{ Pos.x,Pos.y,TILE_WIDTH*tam*7,TILE_HEIGHT*tam*3 }, "Tuberia") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR; 
		body->CreateFixture(&fDef);
	};
	~Tuberia() {};
};
//==============================================================================================
//NAVE
class Nave : public Inanimado
{
public:
	Nave(Juego * Pj, SDL_Point Pos, int tam) :Inanimado(Pj, SDL_Rect{ Pos.x,Pos.y,TILE_WIDTH*tam*5,TILE_HEIGHT*tam*3 }, "Nave") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Nave() {};
};

//==============================================================================================
//CHATARRA
class Chatarra : public Inanimado
{
public:
	Chatarra(Juego * Pj, SDL_Point Pos, int tam) :Inanimado(Pj, SDL_Rect{ Pos.x,Pos.y,TILE_WIDTH*tam * 5,TILE_HEIGHT*tam * 3 }, "Chatarra") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Chatarra() {};
};
#endif // INANIMADO_H_