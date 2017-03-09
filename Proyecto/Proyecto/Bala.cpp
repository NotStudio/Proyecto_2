#include "Bala.h"
#include "checkML.h"

Bala::Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId,float32 vel, int dirx,int diry) :Entidad(punteroJuego, spritePar, objectId)
{

	_vel = vel;
	x = dirx;
	y = diry;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	b2Vec2 Puntos[4];
	Puntos[0] = b2Vec2(0, 0);
	Puntos[1] = b2Vec2(0, sprite->h);
	Puntos[2] = b2Vec2(sprite->w, sprite->h);
	Puntos[3] = b2Vec2(sprite->w,0);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->Set(Puntos, 4);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->CreateFixture(&fDef);
	body->SetUserData(this);
	b2Vec2 velocidad;
	velocidad.x = _vel*x;
	velocidad.y = _vel*y;

	body->SetLinearVelocity(velocidad);
	

	//std::cout << " POS" << pos.x << "\n";
	
	//cout << (body->GetLinearVelocity()).x;
}
Bala::~Bala()
{
}
void Bala::onColisionEnter(Objeto* contactObject) {
	Destruido = false;
	cout << "Bala eliminada";
}
