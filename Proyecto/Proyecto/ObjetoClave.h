#pragma once
#include "Item.h"
class ObjetoClave :
	public Item
{
public:
	ObjetoClave(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~ObjetoClave();
	
};

