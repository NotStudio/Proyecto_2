#ifndef ZONA_JUEGO_H_
#define ZONA_JUEGO_H_
#include "Zona.h"
#include "Juego.h"
#include "Room.h"
#include "Jugable.h"
class ZonaJuego :
	public Zona
{
protected:
	Juego* pJuego;
	//Vector de habitaciones/niveles
	vector<Room*>* niveles;
	//Puntero al nivel actual
	Room* nivelActual;
	//Nombre de la zona para pedir el thilesheet al juego
	std::string id;

public:
	enum RoomType
	{
		Ini,Normal,Boss,Fin,Base
	};
	ZonaJuego(Juego* punteroJuego);
	virtual void initRooms();
	virtual ~ZonaJuego();
	virtual void draw();
	virtual void update();
	virtual SDL_Rect getNivelActual();
	std::string getId() { return id; };
	
};

#endif