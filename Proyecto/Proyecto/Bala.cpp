#include "Bala.h"
#include "checkML.h"

Bala::Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId,float32 vel, int dir) :Entidad(punteroJuego, spritePar, objectId)
{

	_vel = vel;
	direccion = dir;
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
	velocidad.x = 0.0;
	velocidad.y = 0.0;
	if (dir == 1)
		velocidad.y = -(float32)_vel;
	else if (dir == 2)
		velocidad.x = (float32)_vel;
	else if (dir == 3)
		velocidad.y = (float32)_vel;
	else if ( dir == 4)
		velocidad.x = -(float32)_vel;
		
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
