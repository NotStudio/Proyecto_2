#pragma once
#include "Entidad.h"
class Item : public Entidad
{
public:
	Item(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~Item();
};