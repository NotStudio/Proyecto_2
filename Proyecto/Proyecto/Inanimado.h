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
		body->CreateFixture(&fDef);
	}
	virtual ~Inanimado() {
		delete shape; shape = nullptr;
	};
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
	~Tuberia() {};

private:

};

#endif // INANIMADO_H_