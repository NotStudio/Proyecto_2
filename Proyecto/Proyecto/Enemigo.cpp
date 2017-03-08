#include "Enemigo.h"


Enemigo::Enemigo(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : NPC(punteroJuego,spritePar,objectId)
{
}


Enemigo::~Enemigo()
{
}

void Enemigo::onColisionEnter(Objeto* contactObject) {

	std::cout << "HAs muerto por tocar a un enemigo... ¯\_(ツ)_/¯ "  << static_cast<Entidad*>(contactObject)->getId();

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
	move();

}