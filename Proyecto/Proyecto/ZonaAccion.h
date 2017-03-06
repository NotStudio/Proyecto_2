#pragma once
#include "zonaJuego.h"
#include "Entidad.h"
#include "Room.h"
#include <vector>
using namespace std;
class ZonaAccion :
	public ZonaJuego
{
	//Vector de habitaciones/niveles
	vector<Room*> niveles;
	//Enemigos
	vector<Objeto*> enemigos;
	//Objetos colisionables: cofres, rocas, mierda en general.
	vector<Objeto*> obEntorno;
	//Puntero al nivel actual
	Room* nivelActual;

	void setNivelActual();



public:
	ZonaAccion(Juego* punteroJuego);
	virtual ~ZonaAccion();

	virtual void draw();

	virtual void update();
};

