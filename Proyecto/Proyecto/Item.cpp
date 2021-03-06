#include "Item.h"


Item::Item(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : Entidad(punteroJuego, spritePar, objectId)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = true;
	body = punteroJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0.5;
	fDef.filter.categoryBits = Juego::ITEM;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO;
	body->CreateFixture(&fDef);
	body->GetFixtureList()->SetSensor(true);

	origPosY = sprite->y;
	body->SetLinearVelocity(b2Vec2{ 0, velLevitacion });
}


Item::~Item()
{

}

void Item::update() {
	Entidad::update();
	levitar();
}

//void Item::onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2){}

void Item::levitar(){
	if (sprite->y >= origPosY + diferenciaPos) {
		body->SetLinearVelocity(b2Vec2{ 0, -velLevitacion });
	}
	else if (sprite->y <= origPosY - diferenciaPos) {
		body->SetLinearVelocity(b2Vec2{ 0, velLevitacion });
	}

}