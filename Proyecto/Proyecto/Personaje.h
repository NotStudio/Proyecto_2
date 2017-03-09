#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "Entidad.h"
class Personaje :
	public Entidad
{
public:
	Personaje(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~Personaje();

	void virtual update();
	int getVidas(){ return stats.vida; };
	void restaVidas(int numero) { stats.vida -= numero; };
protected:

	struct atributos {
		int vida;
		int daño;
		int velMov;
		int velAtq;
	} stats;

	vector<Objeto*> inventario;


};

#endif