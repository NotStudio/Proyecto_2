#include "Room.h"
#include "TileInfo.h"
#include <string>
#include<sstream>
#include <iostream>
//Construye habitacion apartir de un texto.


//cosas arcaicas y viejunas del mundo 
/*
/*
switch (Salida.DirPuerta)
{
case Puerta::Direcciones::Norte:
world->DestroyBody(Tiles[maxX / 2-1]->getBody());
Tiles[maxX / 2-1]->SetTile(S1);
Tiles[maxX / 2-2]->SetTile(ISE);
Tiles[maxX / 2]->SetTile(ISO);
Salida.posicion = Tiles[maxX / 2 - 1]->getBox();
break;
case Puerta::Direcciones::Sur:
world->DestroyBody(Tiles[Tiles.size() - maxX / 2-1]->getBody());
world->DestroyBody(Tiles[Tiles.size() - maxX / 2 -2]->getBody());
Tiles[Tiles.size()-maxX / 2-1]->SetTile(S1);
Tiles[Tiles.size() - maxX / 2-2]->SetTile(S1);
Tiles[Tiles.size() - maxX / 2 - 3]->SetTile(INE);
Tiles[Tiles.size() - maxX / 2]->SetTile(INO);
Salida.posicion = Tiles[Tiles.size() - maxX / 2 - 1]->getBox();
break;
case Puerta::Direcciones::Este:
world->DestroyBody(Tiles[(maxX)*((Tiles.size() / maxX) / 2)]->getBody());
Tiles[(maxX)*((Tiles.size()/maxX)/2)]->SetTile(S1);
Tiles[(maxX)*(((Tiles.size() / maxX) / 2)+1)]->SetTile(INE);
Tiles[(maxX)*(((Tiles.size() / maxX) / 2) -1)]->SetTile(ISE);
Salida.posicion = Tiles[(maxX)*((Tiles.size() / maxX) / 2)]->getBox();
break;
case Puerta::Direcciones::Oeste:
world->DestroyBody(Tiles[(maxX)*(((Tiles.size() / maxX) / 2) + 1) - 1]->getBody());
world->DestroyBody(Tiles[(maxX)*(((Tiles.size() / maxX) / 2)) - 1]->getBody());
Tiles[(maxX)*(((Tiles.size() / maxX) / 2) + 1)-1]->SetTile(S1);
Tiles[(maxX)*(((Tiles.size() / maxX) / 2)+2)-1]->SetTile(INO);
Tiles[(maxX)*(((Tiles.size() / maxX) / 2)-1)-1]->SetTile(ISO);
Tiles[(maxX)*(((Tiles.size() / maxX) / 2)) - 1]->SetTile(S1);
Salida.posicion = Tiles[(maxX)*(((Tiles.size() / maxX) / 2) + 1) - 1]->getBox();
Salida.posicion.h += TILE_HEIGHT;
break;
default:
break;
}
if (entrada!=nullptr)
{
string Distinguidor = direccion.substr( direccion.find_last_of('_')+1);
if (entrada->DirPuerta == Puerta::Oeste) {
if (Distinguidor == "Grande.map"&&entrada->zonaPuerta.w == TILE_WIDTH * 16) {
IniX = entrada->posicion.x + TILE_WIDTH;
IniY = entrada->zonaPuerta.y - 2*TILE_HEIGHT;
}
else if (Distinguidor == "Peque.map"&&entrada->zonaPuerta.w > TILE_WIDTH * 16) {
IniX = entrada->posicion.x + TILE_WIDTH;
IniY = entrada->zonaPuerta.y + 2 * TILE_HEIGHT;
}
else{

IniY = entrada->zonaPuerta.y;
}
IniX = entrada->posicion.x + TILE_WIDTH;
}
else if (entrada->DirPuerta == Puerta::Sur) {
if (Distinguidor == "Grande.map"&&entrada->zonaPuerta.w == TILE_WIDTH * 16) {
IniX = entrada->zonaPuerta.x - 2 * TILE_WIDTH;
IniY = entrada->posicion.y + TILE_HEIGHT;
}
else if (Distinguidor == "Peque.map"&&entrada->zonaPuerta.w > TILE_WIDTH * 16) {
IniX = entrada->zonaPuerta.x + 2*TILE_WIDTH;
IniY = entrada->posicion.y + TILE_HEIGHT;
}
else {
IniX = entrada->zonaPuerta.x;
IniY = entrada->posicion.y+TILE_HEIGHT;
}
}
}
if (entrada!=nullptr)
{
switch (entrada->DirPuerta)
{
case Puerta::Norte:
vis = true;
break;
case Puerta::Sur:
if (entrada->posicion.y + TILE_WIDTH == y)
{
if (entrada->posicion.x == x)
{
Tiles.push_back(new Tile(x, y, S1, world));
vis = true;
}
else if (entrada->posicion.x + TILE_HEIGHT == x)
{
Tiles.push_back(new Tile(x, y, ISO, world));
vis = true;
}
else if (entrada->posicion.x - TILE_HEIGHT == x)
{
Tiles.push_back(new Tile(x, y, S1, world));
vis = true;
}
else if (entrada->posicion.x - 2*TILE_HEIGHT == x)
{
Tiles.push_back(new Tile(x, y, ISE, world));
vis = true;
}
}
break;
case Puerta::Oeste:
if (entrada->posicion.x+TILE_WIDTH==x)
{
if (entrada->posicion.y == y)
{
Tiles.push_back(new Tile(x, y, S1, world));
vis = true;
}
else if (entrada->posicion.y + TILE_HEIGHT == y)
{
Tiles.push_back(new Tile(x, y, INE, world));
vis = true;
}
else if (entrada->posicion.y - TILE_HEIGHT == y)
{
Tiles.push_back(new Tile(x, y, S1, world));
vis = true;
}
else if (entrada->posicion.y - 2*TILE_HEIGHT == y)
{
Tiles.push_back(new Tile(x, y, ISE, world));
vis = true;
}
}
break;
case Puerta::Este:
break;
default:
break;
}

}
*/
/*
vector<Tile*> RoomMinima(b2World * world,int& WID, int& HEI, int xIni,int yIni){
	int Ancho = 16;
	int Alto = 12;
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x=xIni, y=yIni;
	int posY=0, posX=0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX==0||posX==Ancho-1)?((posX==0)?SE:SO):PH , world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho-1) && (posY != Alto / 2)) ? ((posX == 0) ? NE : NO) : PH, world));
		else 
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho -1) && !(posY == Alto / 2 || posY == (Alto / 2)-1)) ? ((posX == 0) ? PV : PV) : S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = xIni;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}
	}
	WID = Ancho*TILE_WIDTH;
	HEI = Alto*TILE_HEIGHT;
	cout << WID << " " << HEI;
	return Tiles;
}
vector<Tile*> RoomCustom(b2World * world,int Ancho,int Alto ,int& WID, int& HEI, int xIni, int yIni,Direcciones LocPuert) {
	vector<Tile*> Tiles;
	Tiles.reserve(Alto*Ancho);
	int x = xIni, y = yIni;
	int posY = 0, posX = 0;
	for (size_t i = 0; i < Ancho*Alto; i++)
	{
		if (posY == 0)
			Tiles.push_back(new Tile(x, y, (posX == 0 || posX == Ancho - 1) ? ((posX == 0) ? SE : SO) : (LocPuert.Norte && (posX == Ancho / 2 || posX == (Ancho / 2) - 1)) ? S1 : PH, world));
		else if (posY == Alto - 1)
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho - 1) && (posY != Alto / 2)) ? ((posX == 0) ? NE : NO) : (LocPuert.Sur && (posX == Ancho / 2 || posX == (Ancho / 2) - 1)) ? S1 : PH, world));
		else if (LocPuert.Este && (posY == Alto / 2 || posY == Alto / 2 - 1))
			Tiles.push_back(new Tile(x, y, S1, world));
		else if (LocPuert.Oeste && (posY == Alto / 2 || posY == Alto / 2 - 1))
			Tiles.push_back(new Tile(x, y, S1, world));
		else
			Tiles.push_back(new Tile(x, y, ((posX == 0 || posX == Ancho - 1)&& !((LocPuert.Este||LocPuert.Oeste)&&(posY==Alto/2|| posY == (Alto / 2)-1)))? ((posX == 0) ? PV : PV) :S1, world));
		x += TILE_WIDTH;
		posX++;
		if (posX == Ancho) {
			x = xIni;
			posX = 0;
			y += TILE_HEIGHT;
			posY++;
		}
	}
	WID = Ancho*TILE_WIDTH;
	HEI = Alto*TILE_HEIGHT;
	cout << WID << " " << HEI;
	return Tiles;
}
*/
