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
		b2Vec2 Puntos[4];
		Puntos[0] = b2Vec2(0, 0);
		Puntos[1] = b2Vec2(0, sprite->h);
		Puntos[2] = b2Vec2(sprite->w,sprite->h );
		Puntos[3] = b2Vec2(sprite->w,0 );
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->Set(Puntos, 4);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
	}
	virtual ~Inanimado() {};
	virtual void onColisionEnter(Objeto * o = nullptr) {};
};
class Agujero:
	public Inanimado
{
public:
	Agujero(Juego * Pj, SDL_Point Pos, int tam) :Inanimado(Pj, SDL_Rect{Pos.x,Pos.y,tam,tam}, "agujero") {}
	~Agujero() {};
private:

};
class Tuberia: public Inanimado
{
public:
	Tuberia(Juego * Pj, SDL_Point Pos, int tam) :Inanimado(Pj, SDL_Rect{ Pos.x,Pos.y,tam,tam }, "tuberia") {};
	~Tuberia();

private:

};

#endif // INANIMADO_H_