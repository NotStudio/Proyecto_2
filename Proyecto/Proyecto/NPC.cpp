#include "NPC.h"



NPC::NPC(Juego* punteroJuego, SDL_Rect spritePar, string objectId): Personaje(punteroJuego, spritePar, objectId)
{
	//Fisica
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((float32)sprite.x, (float32)sprite.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox((float32)sprite.w / 2, (float32)sprite.h / 2);
	fDef.shape = shape; fDef.density = 5000.0f; fDef.friction = 1.0f;
	body->CreateFixture(&fDef);
	stats.velMov = 1.0;


	
}


NPC::~NPC()
{
	

}

void NPC::onColisionEnter(Objeto* contactObject) {

	std::cout << "colision gatete";
}
