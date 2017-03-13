#include <fstream>
#include<stdio.h>
#include "Room.h"
#include "checkML.h"
#include "constructoraRooms.h"
#include "Perseguidor.h"
#include "EnemigoBomba.h"
#include "MaquinaDePelotas.h"
#include "MaquinaDePelotas.h"
#include "Inanimado.h"
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


void Room::update()
{
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->update();
	}

	


}

Room::Room(Juego * pJ, int x, int y, Puerta puerta) :pJuego(pJ)
{
	string a = "tilesheet";
	string b = "zon1";
	textTiles = new Tilesheet(24, pJuego->getTextura(a,b));
	a = "../Material/tutorial1.map";
	Tiles = new vector<Tile*>(RoomDesdeArchivo(a,pJuego->getWorld(),ANCHO_NIVEL,ALTO_NIVEL));
	//setTiles(DirM, wardo);
	area = new SDL_Rect{ x,y,ANCHO_NIVEL,ALTO_NIVEL };
	int xp = 0, yp = 0;
	//Crear el vector de enemigos, leer de archivos.
	SDL_Rect r2, r3,r4;
	r2.x = x + 750;
	r2.y = y + 500;
	r2.h = 50;
	r2.w = 50;
	r3.x = Tiles->at(getTileOcupable())->getBox().x;
	r3.y = Tiles->at(getTileOcupable())->getBox().y;
	r3.h = 50;
	r3.w = 50;
	r4.x = x + 300;
	r4.y = y + 100;
	r4.h = 50;
	r4.w = 50;
	//enemigos.push_back(new Enemigo(pJuego, r2, "Gato"));
	enemigos.push_back(new Perseguidor(pJuego, r3));
	objetos.push_back(new Agujero(pJuego, SDL_Point{100,100},100));
	//enemigos.push_back(new MaquinaDePelotas(pJuego, r4));
	//Crear vector de objetos inanimados.
	
}
bool Room::setTiles(string Dirm,b2World * wardo) {
	
	int x = 0;
	int y = 0;
	return true;
}
int Room::getTileOcupable()
{
	srand(SDL_GetTicks());
	int k = rand()%Tiles->size();
	while (Tiles->at(k)->getType()>11)
	{
		k = rand() % Tiles->size();
	}
	return k;
}
Room::~Room()
{
	for (size_t i = 0; i < enemigos.size(); i++)
	{
		delete enemigos[i];
		enemigos[i] = nullptr;
	}
	for (size_t i = 0; i < objetos.size(); i++)
	{
		delete objetos[i];
		objetos[i] = nullptr;
	}
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		delete Tiles->at(i);
		Tiles->at(i) = nullptr;
	}
	delete textTiles;
	textTiles = nullptr;
	delete area;
	delete Tiles;
	Tiles = nullptr;

	//limpiar enemigos.
}
void Room::DestroyRoom(b2World * wardo)
{
	for (size_t i = 0; i < Tiles->size(); i++)
	{
			wardo->DestroyBody(Tiles->at(i)->getBody());
	}
}
void Room::render(){
	//Dibujamos los tiles de fondo.
	SDL_Rect Dibujar;
	int tipoDeTile;
	for (size_t i = 0; i < Tiles->size(); i++)
	{
		 if (Tiles->at(i)->render(&pJuego->getCameraRect(),Dibujar,tipoDeTile)) {

			 textTiles->draw(pJuego->getRender(), Dibujar, tipoDeTile, pJuego->getCamera());
		}
	}
	//Dibujamos enemigos y objetos.
	for (int i = 0; i < objetos.size(); i++) {
		objetos[i]->draw();
	}
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->draw();
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

void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}


}
