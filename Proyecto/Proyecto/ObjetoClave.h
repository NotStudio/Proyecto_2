#ifndef OBJETO_CLAVE_H_
#define OBJETO_CLAVE_H_

#include "Item.h"
class ObjetoClave :
	public Item
{
public:
	ObjetoClave(Juego* punteroJuego, SDL_Rect spritePar);
	~ObjetoClave();
	
	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2);
};

#endif