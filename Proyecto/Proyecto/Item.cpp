#include "Item.h"


Item::Item(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : Entidad(punteroJuego, spritePar, objectId)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = true;
	body = punteroJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
	fDef.shape = shape; fDef.density = 1.0f; fDef.friction = 0.5;
	fDef.filter.categoryBits = Juego::ITEM;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO;
	body->CreateFixture(&fDef);

}


Item::~Item()
{

}

void Item::update() {
	Entidad::update();
}
