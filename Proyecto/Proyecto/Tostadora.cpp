#include "Tostadora.h"



Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	//Física
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite.w / 2, sprite.h / 2);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 1.0f;
	body->CreateFixture(&fDef);

	stats.velMov = 300;


	
	
}


Tostadora::~Tostadora()
{
	pJuego->getWorld()->DestroyBody(body);
}

void Tostadora::onColisionEnter(Objeto* contactObject) {

	std::cout << "colision";

}
