#ifndef OBJETO_HISTORICO_H_
#define OBJETO_HISTORICO_H_

#include "Item.h"
class ObjetoHistorico :
	public Item
{
public:

	ObjetoHistorico(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int cantidad);
	~ObjetoHistorico();
	int getCantidad(){ return cantidad_; };
	void sumarCantidad(int x){
		cantidad_ += x;
	}

	bool restarCantidad(int x){
		if (cantidad_ - x >= 0){
			cantidad_ -= x;
			return true;
		}
		else return false;

	}


private:
	int cantidad_;
	string tipo;

	virtual void onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2);
};

#endif