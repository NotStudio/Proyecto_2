#include "Bala.h"
#include "checkML.h"

Bala::Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry, int lanzador) :Entidad(punteroJuego, spritePar, objectId), lanzador(lanzador)
{

	_vel = vel;
	x = dirx;
	y = diry;
	cout << x;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->CreateFixture(&fDef);
	body->SetUserData(this);
	b2Vec2 velocidad;
	velocidad.x = _vel*x;
	velocidad.y = _vel*y;
	//Capa de colision.
	if (lanzador == 1){
		fDef.filter.categoryBits = Juego::AT_ENEMIGO;
		fDef.filter.maskBits = Juego::ESCENARIO | Juego::ENEMIGO | Juego::JUGADOR;
	}
	else if (lanzador == 0){
		fDef.filter.categoryBits = Juego::AT_JUGADOR;
		fDef.filter.maskBits = Juego::ESCENARIO | Juego::ENEMIGO;
	}

	fDef.filter.maskBits = Juego::ESCENARIO;
	body->SetLinearVelocity(velocidad);
	
}
Bala::~Bala()
{
	delete shape;
	shape = nullptr;
}
void Bala::onColisionEnter(Objeto* contactObject) {
	destruido = true;
}

int Bala::getLanzador(){
	return lanzador;
}
