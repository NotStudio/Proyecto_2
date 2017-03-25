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
	int getVidas() { return stats.vida; };
	void restaVidas(int numero) { stats.vida -= numero; };
	
	struct atributos {
		int vida;        int vidaLim;
		int vidaMax;	int vidaMaxLim;
		int daño;		int dañoLim;
		int velMov;		int velMovLim;
		int velAtq;		int velAtqLim;

		 struct atributos& operator+=(atributos const &a) {

			 if (vida + a.vida <= vidaLim)
				vida += a.vida;
			 if (vidaMax + a.vidaMax <= vidaMaxLim)
				vidaMax += a.vidaMax;
			 if (daño + a.daño <= dañoLim)
				daño += a.daño;
			 if (velMov + a.velMov <= velMovLim)
				velMov += a.velMov;
			 if (velAtq + a.velAtq <= velAtqLim)
				velAtq += a.velAtq;

			return *this;
		}
	};

	void applyEffect(atributos &nwEffect) {
		stats += nwEffect;
	}

protected:
	atributos stats;
	//Tal vez no nos haga falta un vector de objetos.
	vector<Objeto*> inventario;
	vector<std::string> dropPool;


};

#endif