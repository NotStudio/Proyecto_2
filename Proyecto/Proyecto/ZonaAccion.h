#ifndef ZONA_ACCION_H_
#define ZONA_ACCION_H_

#include "ZonaJuego.h"
#include "Objeto.h"
#include <vector>
using namespace std;
class ZonaAccion :
	public ZonaJuego
{
	SDL_Rect tam;
	
	//Enemigos
	vector<Objeto*> enemigos;
	//Objetos colisionables: cofres, rocas, mierda en general.
	vector<Objeto*> obEntorno;
	//Balas en prinsipito
	
	

	void setNivelActual();


	void setRect() {
		int minX, minY, MaxX, MaxY;
		minX = niveles->at(0)->getArea().x;
		minY = niveles->at(0)->getArea().y;
		MaxX = niveles->at(0)->getArea().w + minX;
		MaxY = niveles->at(0)->getArea().h + minY;
		for (size_t i = 1; i < niveles->size(); i++)
		{
			minX = (minX > niveles->at(i)->getArea().x) ? niveles->at(i)->getArea().x : minX;
			minY = (minY > niveles->at(i)->getArea().y) ? niveles->at(i)->getArea().y : minY;
			MaxX = (MaxX < niveles->at(i)->getArea().w+ niveles->at(i)->getArea().x) ? niveles->at(i)->getArea().w + niveles->at(i)->getArea().x : MaxX;
			MaxY = (MaxY < niveles->at(i)->getArea().h+ niveles->at(i)->getArea().y) ? niveles->at(i)->getArea().h + niveles->at(i)->getArea().y : MaxY;
		}
		tam = { minX, minY, MaxX - minX, MaxY - minY };
	}

public:
	ZonaAccion(Juego* punteroJuego);
	virtual ~ZonaAccion();

	virtual void draw();

	virtual void update();
	Room*getNivel(){ return nivelActual; }
	vector<Room*>*getNiveles(){ return niveles; }

};

#endif