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
	
	/*Struct de los ATRIBUTOS. En la constructora de cada personaje, hay que inicializar los atributos con los que empieza.*/
	struct atributos {

		//Atributos		//Límite por arriba						//Límite por abajo
		int vida;       static const int vidaLim = 10;         static const int vidaMin = 0;
		int vidaMax;	static const int vidaMaxLim = 10;	   static const int vidaMaxMin = 0;
		int daño;		static const int dañoLim = 20;	       static const int dañoMin = 1;
		int velMov;		static const int velMovLim = 400;	   static const int velMovMin = 200;
		int velAtq;		static const int velAtqLim = 10;	   static const int velAtqMin = 1;

		atributos() { vida = vidaMax = daño = velMov = velAtq = 0; };

		//Sobrecarga del operador que controla que no se sobrepase por arriba ni por abajo.
		 struct atributos& operator+=(atributos const &a) {
			 //Controlamos que no se le pueda añadir mas del límite ni quitar menos que el mínimo.
			/* if (vida + a.vida <= vidaLim && vida + a.vida >= vidaMin) vida += a.vida;
			 else  if (vida + a.vida < vidaMin) vida = vidaMin;*/
			 vida += a.vida;
			 if (vida < vidaMin) vida = vidaMin;
			 else if (vida > vidaLim) vida = vidaLim;

			 vidaMax += a.vidaMax;
			 if (vidaMax < vidaMaxMin) vidaMax = vidaMaxMin;
			 else if (vidaMax > vidaMaxLim) vidaMax = vidaMaxLim;

			 daño += a.daño;
			 if (daño < dañoMin) daño = dañoMin;
			 else if (daño > dañoLim) daño = dañoLim;

			 velMov += a.velMov;
			 if (velMov < velMovMin) velMov = velMovMin;
			 else if (velMov > velMovLim) velMov = velMovLim;

			 velAtq += a.velAtq;
			 if (velAtq < velAtqMin) velAtq = velAtqMin;
			 else if (velAtq > velAtqLim) velAtq = velAtqLim;
			 
			return *this;
		}
	};

	//Método que utilizan los objetos para sumar sus stats a los del jugador.
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