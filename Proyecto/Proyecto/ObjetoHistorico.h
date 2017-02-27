#pragma once
#include "Item.h"
class ObjetoHistorico :
	public Item
{
public:

	ObjetoHistorico(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	~ObjetoHistorico();
	int getCantidad(){ return cantidad; };
	void sumarCantidad(int x){
		cantidad += x;

	}

	bool restarCantidad(int x){
		if (cantidad - x >= 0){
			cantidad -= x;
			return true;
		}
		else return false;

	}


private:
	int cantidad = 0;
	string tipo;
};

