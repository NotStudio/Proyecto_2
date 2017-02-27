#pragma once
#include "Entidad.h"
class Personaje :
	public Entidad
{
public:
	Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~Personaje();

	void virtual update();

protected:

	struct atributos {
		int vida;
		int daño;
		int velMov;
		int velAtq;
	} stats;

	vector<Objeto*> inventario;


};

