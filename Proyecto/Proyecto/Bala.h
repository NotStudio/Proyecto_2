#ifndef BALA_H
#define BALA_H

#include "Entidad.h"
class Bala :
	public Entidad
{

	float32 _vel;
	int lanzador;
	float32 x,y; //1 arriba ,2 derechas, 3 abjo y 4 adivinalo
public:
	//lanzador: id enemigo o alido.
	Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId,float32 vel,float32 dirx,float32 diry, int lanzador);
	Bala(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry, int lanzador,string sensor);//Bala sensor
	~Bala();
	virtual void onColisionEnter(Objeto* contactObject);
	int getLanzador();
};
#endif
