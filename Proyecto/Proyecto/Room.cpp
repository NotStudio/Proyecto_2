#include "Room.h"
#include <fstream>
#include <SDL.h>
#include "TexturasSDL.h"
#include<stdio.h>
#include<string.h>
#include "checkML.h"
#include "constructoraRooms.h"
//Tile constants
const int TIL_WIDTH = 50;
const int TIL_HEIGHT = 50;
int MAP_T_WIDTH;
int MAP_T_HEIGHT;
const int TOTAL_TILE_SPRITES = 12;
//The different tile sprites
/*
const int S1 = 0;
const int S2 = 1;
const int S3= 2;
const int S4= 3;
const int PV= 4;
const int PH= 5;
const int NE= 6;
const int SE= 7;
const int NO= 8;
const int SO= 9;
const int IP= 10;
const int NA= 11;
*/


void Room::SetRoom(Direcciones p)
{
	RoomCustom(pJuego->getWorld(), 15, 12, ANCHO_NIVEL, ALTO_NIVEL, area->x, area->y, p);
}

void Room::update()
{

	if (dentroRoom(&pJuego->getCamera()->getTargetCentro()))
		pJuego->getCamera()->setLimite(*area);
}

Room::Room(Juego * pJ, int x, int y, Direcciones LocPort) :pJuego(pJ)
{
	Tiles = new vector<Tile*>(RoomCustom(pJuego->getWorld(), 19, 12, ANCHO_NIVEL, ALTO_NIVEL, x, y, LocPort));
	//setTiles(DirM, wardo);
	area = new SDL_Rect{ x,y,ANCHO_NIVEL,ALTO_NIVEL };
	int xp = 0, yp = 0;
	for (size_t i = 0; i < TOTAL_TILE_SPRITES; i++)
	{
		TileSheetRect.push_back(new SDL_Rect{ xp,yp,16,16 });
		xp += 16;
		if (xp >= 16 * 4) { xp = 0; yp += 16; }
	}
	
}

bool Room::setTiles(string Dirm,b2World * wardo) {
	
	int x = 0;
	int y = 0;
	for (size_t i = 0; i < TOTAL_TILE_SPRITES; i++)
	{
		TileSheetRect.push_back(new SDL_Rect{ x,y,16,16 });
		x += 16;
		if (x >= 16*4) {x = 0;y += 16;}
	}
	return true;
}
Room::~Room()
{
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		delete Tiles->at(i);
		Tiles->at(i) = nullptr;
	}
	for (size_t i = 0; i < TileSheetRect.size(); i++)
	{
		delete TileSheetRect[i];
	}
	delete area;
	delete Tiles;
	Tiles = nullptr;
}
void Room::DestroyRoom(b2World * wardo)
{
	for (size_t i = 0; i < Tiles->size(); i++)
	{
			wardo->DestroyBody(Tiles->at(i)->getBody());
	}
}
void Room::render(){
	SDL_Rect Dibujar;
	int tipoDeTile;
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		 if (Tiles->at(i)->render(&pJuego->getCameraRect(),Dibujar,tipoDeTile)) {

			pJuego->getTilesheet()->draw(pJuego->getRender(),Dibujar, TileSheetRect[tipoDeTile],pJuego->getCamera());
		}
	}
}

int Room::encontrarPosicionTiled(int& const x, int& const y)
{
	return(ANCHO_NIVEL / TILE_WIDTH)*((y - (y%TILE_HEIGHT))-1)/TILE_HEIGHT+(1 + (x - (x%TILE_WIDTH)) / TILE_WIDTH);
}
vector<int> Room::TilesOcupados(SDL_Rect & const recto)
{
	int x = recto.x, y = recto.y;
	vector<int>marcados;
	bool flag = true, flag2 = true;
	while (flag) {
		while (flag2)
		{
			int pos = encontrarPosicionTiled(x, y);
			if(Tiles->at(pos)->getType()<4)marcados.push_back(pos);
			if (y > recto.y + recto.h) flag2= false;
			y += TILE_WIDTH;
		}
		y = recto.y;
		if (x > recto.x + recto.w)flag = false;
		flag2 = true;
	}
	return marcados;
}

void Room::SetRoomFichero(string Dir)
{
	RoomDesdeArchivo(Dir, pJuego->getWorld(), ANCHO_NIVEL, ALTO_NIVEL);
}
