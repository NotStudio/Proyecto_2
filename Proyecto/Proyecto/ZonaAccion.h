#ifndef ZONA_ACCION_H_
#define ZONA_ACCION_H_

#include "Juego.h"
#include "zonaJuego.h"
#include "Objeto.h"
#include "Room.h"
#include <vector>
using namespace std;
class ZonaAccion :
	public ZonaJuego
{
	Juego* pJuego;
	//Vector de habitaciones/niveles
	vector<Room*> niveles;
	//Enemigos
	vector<Objeto*> enemigos;
	//Objetos colisionables: cofres, rocas, mierda en general.
	vector<Objeto*> obEntorno;
	//Balas en prinsipito
	
	//Puntero al nivel actual
	Room* nivelActual;

	void setNivelActual();




public:
	ZonaAccion(Juego* punteroJuego);
	virtual ~ZonaAccion();

	virtual void draw();

	virtual void update();
	Room*getNivel(){ return nivelActual; }
	SDL_Rect getNivelActual();
};

#endif