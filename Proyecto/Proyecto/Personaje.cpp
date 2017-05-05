#include "Personaje.h"



Personaje::Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Entidad(punteroJuego,spritePar,objectId)
{
	//Física
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation = true;
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { ((float)sprite->w / PPM) / 2, ((float)sprite->h / PPM) / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
}


Personaje::~Personaje()
{
	

}

void Personaje::update() {

	Entidad::update();
}
