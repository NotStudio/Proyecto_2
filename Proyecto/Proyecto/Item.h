#ifndef ITME_H_
#define ITEM_H_

#include "Entidad.h"
class Item : public Entidad
{
public:
	Item(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~Item();
	virtual void update();
};
#endif