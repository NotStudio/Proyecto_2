#pragma once
#include "Room.h"
class Nivel
{
private:
	vector<Room*>rooms;
	Juego*pJuego;
	int currentRoom;
	int nRooms;
public:
	void genNivel();
	void update();
	void draw();
	Nivel(Juego*,int numRooms);
	Nivel();
	~Nivel();
};

