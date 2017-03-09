#ifndef OBJETO_CLAVE_H_
#define OBJETO_CLAVE_H_

#include "Item.h"
class ObjetoClave :
	public Item
{
public:
	ObjetoClave(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~ObjetoClave();
	
};

#endif