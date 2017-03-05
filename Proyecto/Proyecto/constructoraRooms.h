#include "Room.h"
#include "TileInfo.h"
vector<Tile*> RoomMinima(b2World * world,int& WID, int& HEI){
	int Ancho = 16;
	int Alto = 12;
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x=0, y=0;
	int posY=0, posX=0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX==0||posX==Ancho-1)?((posX==0)?SE:SO):PH , world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho-1) ? ((posX == 0) ? NE : NO) : PH, world));
		else 
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho -1) ? ((posX == 0) ? PV : PV) : S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = 0;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}
	}
	WID = Ancho*TILE_WIDTH;
	HEI = y;
	return Tiles;
}
vector<Tile*> Room2x1(b2World * world, int& WID,int& HEI) {
	int Ancho = 16+5;
	int Alto = 12;
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x = 0, y = 0;
	int posY = 0, posX = 0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? SE : SO) : PH, world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? NE : NO) : PH, world));
		else
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? PV : PV) : S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = 0;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}

	}
	WID = Ancho*TILE_WIDTH;
	HEI = y;
	return Tiles;
}
