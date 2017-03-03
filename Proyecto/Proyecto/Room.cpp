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


Room::Room(string DirM,TexturasSDL * t,SDL_Renderer * pR, b2World * wardo)
{
	Tiles = new vector<Tile*>(RoomMinima(wardo,ANCHO_NIVEL,ALTO_NIVEL));
	kek = t;
	pRend = pR;
	//setTiles(DirM, wardo);
	int x = 0, y = 0;
	for (size_t i = 0; i < TOTAL_TILE_SPRITES; i++)
	{
		TileSheetRect.push_back(new SDL_Rect{ x,y,16,16 });
		x += 16;
		if (x >= 16 * 4) { x = 0; y += 16; }
	}
	
}
Room::Room() {
	Tiles = nullptr;
	pRend = nullptr;
	kek = nullptr;
}

bool Room::setTiles(string Dirm,b2World * wardo) {
	ifstream map(Dirm);
	map >> MAP_T_WIDTH >> MAP_T_HEIGHT;
	int TOT_Tiles = MAP_T_WIDTH*MAP_T_HEIGHT;
	Tiles->reserve(TOT_Tiles);
	int x = 0, y = 0;
	for (size_t i = 0; i < TOT_Tiles; i++)
	{
		
		int tipo = -1;
		map >> tipo;
		if (tipo >= 0 && tipo < TOTAL_TILE_SPRITES)
			Tiles->push_back(new Tile(x, y, tipo,wardo));
		x += TILE_WIDTH;
		if (x >= TILE_WIDTH*MAP_T_WIDTH) {
			x = 0;
			y += TILE_HEIGHT;
		}
	}
	x = 0;
	y = 0;
	for (size_t i = 0; i < TOTAL_TILE_SPRITES; i++)
	{
		TileSheetRect.push_back(new SDL_Rect{ x,y,16,16 });
		x += 16;
		if (x >= 16*4) {x = 0;y += 16;}
	}
	map.close();
	return true;
}
Room::~Room()
{
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		delete Tiles->at(i);
		Tiles->at(i) = nullptr;
	}
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
void Room::render(Camara* camara){
	int maldito = encontrarPosicionTiled(camara->getTarget());
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		if (i == maldito + 1|| i == maldito - 1 || i == maldito - (ANCHO_NIVEL / TILE_WIDTH))
		{
		}
		else if (Tiles->at(i)->Dentro(&camara->getPlano())) {
			if (Tiles->at(i)->getType() > 2)
				Tiles->at(i)->setPos(1,1);
			SDL_Rect rel = Tiles->at(i)->getBox();
			rel.x -= camara->getPlano().x;
			rel.y -= camara->getPlano().y;
			kek->draw(pRend, rel, TileSheetRect[Tiles->at(i)->getType()]);
		}
	}
}

int Room::encontrarPosicionTiled(SDL_Rect & const recto)
{
	int x = recto.x+recto.w/2, y = recto.y + recto.h / 2;
	return(ANCHO_NIVEL / TILE_WIDTH)*((y - (y%TILE_HEIGHT))-1)/TILE_HEIGHT+(1 + (x - (x%TILE_WIDTH)) / TILE_WIDTH);
}


