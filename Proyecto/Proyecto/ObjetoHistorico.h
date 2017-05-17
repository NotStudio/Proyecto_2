#ifndef OBJETO_HISTORICO_H_
#define OBJETO_HISTORICO_H_

#include "Item.h"

class ObjetoHistorico : public Item
	
{
public:

	ObjetoHistorico(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int cantidad);
	~ObjetoHistorico();

private:
	int cantidad_;
	string tipo;

	virtual void onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2);
	
};

#endif