#include "Personaje.h"



Personaje::Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Entidad(punteroJuego,spritePar,objectId)
{
}


Personaje::~Personaje()
{
}

void Personaje::update() {

	Entidad::update();
}
