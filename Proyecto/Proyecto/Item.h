#ifndef ITEM_H_
#define ITEM_H_
#include "Entidad.h"

class Item : public Entidad
{
	const int diferenciaPos = 8;
	const float32 velLevitacion = 0.05f;
	float origPosY;
public:
	Item(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~Item();
	virtual void update();
	//virtual void onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2);
	void levitar();
};
#endif