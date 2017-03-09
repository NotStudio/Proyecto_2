#include "Enemigo.h"


Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : NPC(punteroJuego,spritePar,objectId)
{
	//Fisica

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2);
	fDef.shape = shape; fDef.density = 5000.0f; fDef.friction = 0.5f;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO;
	body->CreateFixture(&fDef);

}


Enemigo::~Enemigo()
{
	delete shape;
}

void Enemigo::onColisionEnter(Objeto* contactObject) {

	std::cout << "HAs muerto por tocar a un enemigo: "  << dynamic_cast<Entidad*>(contactObject)->getId() << "\n";

}
void Enemigo::move(){
	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;
	if (x> pos.x)velFloat.x = 1.0f;
	if (x< pos.x)velFloat.x =  -1.0f;
	if (y> pos.y)velFloat.y = 1.0f;
	if (y< pos.y)velFloat.y = -1.0f;
	body->SetLinearVelocity(velFloat);
}
void  Enemigo::update(){
	Entidad::update();
	

}

void Enemigo::stop() {
	body->SetLinearVelocity(b2Vec2{ 0,0 });
}