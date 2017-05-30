#ifndef ZONA_ACCION_H_
#define ZONA_ACCION_H_

#include "ZonaJuego.h"
#include "Objeto.h"
#include <vector>
using namespace std;
class ZonaAccion :
	public ZonaJuego
{
private:
	bool CheckSolapaRooms(const SDL_Rect& R);
	SDL_Rect tam;
protected:
	void BuildIniRoom(size_t Planta = 0);
	void BuildFinRoom(size_t Planta = 0);
	void BuildRoom(RoomType RoomType_,size_t Planta=0);
	SDL_Point getPosiblePositionRoom(TMXReader::MapData* Data_,Direcciones&);
	vector<pair<SDL_Point,Direcciones>>getPosicionesLados(Room* Room_,SDL_Rect&Rect_);
	// cuantas habitaciones sin contar la del Boss y las vacias, y cuantos descansos.
	void setHabitaciones(int NumeroHabitaciones, int NumeroParones);
	//Inicializa la varible nivelActual a la habitación en la que se encuentra el jugador.
	void setNivelActual();
	//Método de Fran
	void setRect() {
		int minX, minY, MaxX, MaxY;
		minX = niveles->at(0)->getArea()->x;
		minY = niveles->at(0)->getArea()->y;
		MaxX = niveles->at(0)->getArea()->w + minX;
		MaxY = niveles->at(0)->getArea()->h + minY;
		for (size_t i = 1; i < niveles->size(); i++)
		{
			minX = (minX > niveles->at(i)->getArea()->x) ? niveles->at(i)->getArea()->x : minX;
			minY = (minY > niveles->at(i)->getArea()->y) ? niveles->at(i)->getArea()->y : minY;
			MaxX = (MaxX < niveles->at(i)->getArea()->w+ niveles->at(i)->getArea()->x) ? niveles->at(i)->getArea()->w + niveles->at(i)->getArea()->x : MaxX;
			MaxY = (MaxY < niveles->at(i)->getArea()->h+ niveles->at(i)->getArea()->y) ? niveles->at(i)->getArea()->h + niveles->at(i)->getArea()->y : MaxY;
		}
		tam = { minX, minY, MaxX - minX, MaxY - minY };
	}

public:
	ZonaAccion(Juego* punteroJuego);
	virtual ~ZonaAccion();
	virtual void draw();
	virtual void update();
	void dibujarMapa();
	//Devolvemos el nivel actual
	Room*getNivel(){ return nivelActual; }
	//Devolvemos el array de niveles.
	vector<Room*>*getNiveles(){ return niveles; }

};

#endif