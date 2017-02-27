#pragma once
#include "Item.h"
class Consumible :
	public Item
{
public:
	Consumible(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~Consumible();

};
