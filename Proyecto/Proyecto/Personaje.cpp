#include "Personaje.h"



Personaje::Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Entidad(punteroJuego,spritePar,objectId)
{
}


Personaje::~Personaje()
{
	pJuego->getWorld()->DestroyBody(body);

}

void Personaje::update() {

	Entidad::update();
}
