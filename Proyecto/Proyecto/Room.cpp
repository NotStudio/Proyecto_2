#include <fstream>                        
#include<stdio.h>
#include "Room.h"
#include "checkML.h"
#include "constructoraRooms.h"
#include "Perseguidor.h"
#include "EnemigoBomba.h"
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

//Update que realiza la habitacion. Ha de actualizarse todo lo que haya en ella (enemigos, objetos, balas, etc)
void Room::update()
{
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->update();
	}
	for (int i = 0; i < extras.size(); i++) {
		if (extras[i] != nullptr)
		if (!extras[i]->getdestruido())
			extras[i]->update();
		else {
			delete extras[i];
			extras[i] = nullptr;
		}
	}
	for (int i = 0; i < extras.size(); i++) {
		if (extras[i] == nullptr)	{
			extras.erase(extras.begin() + i);
			i--;
		}
	}
}

//Constructora de la habitación. Aquí es donde se lee el nivel, se crea y se añaden los enemigos y objetos.
Room::Room(Juego * pJ,Puerta sal, Puerta * entrada,int x, int y) :pJuego(pJ)
{
	string a = "tilesheet";
	string b = "zon1";
	textTiles = new Tilesheet(24, pJuego->getTextura(a,b));
	a = (entrada==nullptr||entrada->zonaPuerta.w==1024)? "../Material/Maps/mapa_Grande.map": "../Material/Maps/mapa_Peque.map";
	Tiles = new vector<Tile*>(RoomDesdeArchivo(a,pJuego->getWorld(),ANCHO_NIVEL,ALTO_NIVEL,sal,entrada));
	//setTiles(DirM, wardo);
	Salida = sal;
	area = new SDL_Rect{ Tiles->at(0)->getBox().x ,Tiles->at(0)->getBox().y,ANCHO_NIVEL,ALTO_NIVEL };
	Salida.zonaPuerta = *area;
	int xp = 0, yp = 0;


	//Crear el vector de objetos, leer de archivos.
	if (entrada == nullptr) {
		objetos.push_back(new Agujero(pJuego, SDL_Point{ TILE_WIDTH * 3 + area->x, area->w / 2 + TILE_HEIGHT * 7 + area->y }, 150));
		objetos.push_back(new Nave(pJuego, SDL_Point{ area->w - TILE_WIDTH * 5 + area->x, TILE_HEIGHT * 3 + area->y }, TILE_WIDTH * 3));
		objetos.push_back(new Chatarra(pJuego, SDL_Point{ TILE_WIDTH * 1 + area->x, area->w / 2 + TILE_HEIGHT + area->y }, TILE_WIDTH / 4));
		objetos.push_back(new Chatarra(pJuego, SDL_Point{ TILE_WIDTH * 2 + area->x, area->w / 2 + TILE_HEIGHT * 2 + area->y }, TILE_WIDTH / 4));
		objetos.push_back(new Tuberia(pJuego, SDL_Point{ TILE_WIDTH / 2 + area->x, area->w / 2 + TILE_HEIGHT * 7 + area->y }, TILE_WIDTH / 2));
	}
	//Crear vector de enemigos.
	//enemigos.push_back(new Perseguidor(pJuego, SDL_Rect{ area->w / 2 + area->x, area->h /2 + area->y , 64,64 }));
	enemigos.push_back(new EnemigoBomba(pJuego, Tiles->at(getTileOcupable())->getBox()));
	enemigos.push_back(new EnemigoBomba(pJuego, Tiles->at(getTileOcupable())->getBox()));
	enemigos.push_back(new MaquinaDePelotas(pJuego, SDL_Rect{ area->w / 2 + TILE_WIDTH *4 + area->x, area->h /2 +TILE_HEIGHT*4 + area->y , 128,128 }));
	enemigos.push_back(new Perseguidor(pJuego, SDL_Rect{ 500 + area->x,  500 + area->y , 64,64}));
	
}

//Metodo que se llama cuando se sale de la habitación. Se llama al stop de todos lo enemigos, que tienen que dejar de hacer ataques. **ESTO ES PROVISIONAL**
void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}
}

//COSAS DE FRAN
// --------------------------------------------------------------------------------------------------------------


bool Room::setTiles(string Dirm,b2World * wardo) {
	
	int x = 0;
	int y = 0;
	return true;
}
int Room::getTileOcupable()
{
	srand(SDL_GetTicks());	
	int k = rand()%Tiles->size();
	while (Tiles->at(k)->getType()<11)
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
	for (size_t i = 0; i < extras.size(); i++) {
		delete extras[i];
		extras[i] = nullptr;
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
	for (int i = 0; i < extras.size(); i++) {
		extras[i]->draw();
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
//	RoomDesdeArchivo(Dir, pJuego->getWorld(), ANCHO_NIVEL, ALTO_NIVEL);
}


