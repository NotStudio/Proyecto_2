#include <fstream>                        
#include<stdio.h>
#include "Room.h"
#include "checkML.h"
#include "constructoraRooms.h"
#include "Perseguidor.h"
#include "EnemigoBomba.h"
#include "MaquinaDePelotas.h"
#include "Inanimado.h"
#include "factoriaEntidades.h"
#include "MapData.h"
#include "TileInfo.h"
#include <time.h>
#include "Sierra.h"
#include "Helice.h"
#include "ZonaBase.h"
#include "tmxReader.h"
#define DEBUG

void Room::resume(){

	for (int i = 0; i < extras.size(); i++) {
		if (extras[i] != nullptr)
			static_cast<Bala*>(extras[i])->resume();
	}

}
void Room::checkAliveEnemies(int n) {
	if (n >= killableEnemies)
		isEmpty_ = true;

}
//Update que realiza la habitacion. Ha de actualizarse todo lo que haya en ella (enemigos, objetos, balas, etc)
void Room::update()
{ 
	int deadEnemies = 0;
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->update();
		if (static_cast<Enemigo*>(enemigos[i])->isDead())
			deadEnemies++;
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
	checkAliveEnemies(deadEnemies);
	if (RoomState_ == ABIERTA){
		if (!isEmpty_)
		{
			SDL_Rect aux = *area;
			aux.x += TILE_WIDTH;
			aux.y += TILE_WIDTH;
			aux.w -= TILE_WIDTH;
			aux.h -= TILE_WIDTH;
			SDL_IntersectRect(&aux,pJuego->getPlayer()->getRect(),&aux);
			if (SDL_RectEquals(pJuego->getPlayer()->getRect(), &aux)){
				cerrarPuertas();
				RoomState_ = CERRADA;
				pJuego->reproducirEfecto("Door");
			}
		}
	}
	else
	{
		if (isEmpty_){
			abrirPuertas();
			RoomState_ = ABIERTA;
		}
	}
}


//Constructora de la habitación. Aquí es donde se lee el nivel, se crea y se añaden los enemigos y objetos.
//No hace falta meter los parametros string para cargar un tilesheet, carga por defecto el de la zona 1
Room::Room(Juego * pJ, Zona* z, TMXReader::MapData* mdata,SDL_Point Coor):pJuego(pJ), mapdat(mdata), killableEnemies(0), isEmpty_(false)
{
	RoomState_ = ABIERTA;
	area = new SDL_Rect{ Coor.x,Coor.y,mapdat->getLayer()->getW()*TILE_WIDTH,mapdat->getLayer()->getH()*TILE_WIDTH };
	open_ = true;
	zona = z;
	//Si es base, creamos la room de Base
	if (typeid(ZonaBase) == typeid(*zona)){
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
	}
	//Si no, generamos una zona con niveles aleatorios y to la pesca.
	else {
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
	}
	
}
//Constructora de niveles dependiendo del string (Boss o inicial)


//Metodo que se llama cuando se sale de la habitación. Se llama al stop de todos lo enemigos, que tienen que dejar de hacer ataques. **ESTO ES PROVISIONAL**
void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}
	abrirPuertas();

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
	
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		for (size_t j = 0; j < Tiles.at(i).size(); j++)
		{
			delete Tiles.at(i).at(j);
			Tiles.at(i).at(j)=nullptr;
		}
	}
	
	for (size_t i = 0; i < extras.size(); i++) {
		delete extras[i];
		extras[i] = nullptr;
	}

	for (auto p : Puertas) {
		delete p;
		p = nullptr;
	}



	delete textTiles;
	textTiles = nullptr;
	delete area;

	//limpiar enemigos.
}
void Room::marcarOcupados(vector<SDL_Point> const p){
	for (size_t i = 0; i < p.size(); i++)
	{
		ocupados[p[i].x][p[i].y] = true;
	}
}
void Room::setPuertas(Direcciones dirc)
{
	Puertas.push_back(new Puerta(dirc));
}

void Room::initPuertas()
{
	for (auto p:Puertas) {
		
		Direcciones d = p->GetDir();
		switch (d)
		{
		case Norte:
			p->meteTilePuerta(Tiles[0][Tiles.at(0).size() / 2]);
			p->meteTilePuerta(Tiles[0][Tiles.at(0).size() / 2 - 1]);
			break;
		case Este:
			p->meteTilePuerta(Tiles[Tiles.size() / 2][Tiles.at(0).size() - 1]);
			p->meteTilePuerta(Tiles[Tiles.size() / 2 - 1][Tiles.at(0).size() - 1]);
			break;
		case Sur:
			p->meteTilePuerta(Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2]);
			p->meteTilePuerta(Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 1]);
			break;
		case Oeste:
			p->meteTilePuerta(Tiles[Tiles.size() / 2][0]);
			p->meteTilePuerta(Tiles[Tiles.size() / 2 - 1][0]);
			break;
		}
	}
}

void Room::cerrarPuertas()
{
	for (auto puerta : Puertas)
		puerta->cerrarPuerta();
}
void Room::cerrarPuerta(int dicc)
{
	switch (dicc)
	{
	case Direcciones::Norte:
		Tiles[0][Tiles.at(0).size() / 2 - 2]->SetTile(PN);
		Tiles[0][Tiles.at(0).size() / 2]->SetTile(PN);
		Tiles[0][Tiles.at(0).size() / 2 - 1]->SetTile(PN);
		Tiles[0][Tiles.at(0).size() / 2 + 1]->SetTile(PN);
		break;
	case Direcciones::Sur:
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 2]->SetTile(PS);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2]->SetTile(PS);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 1]->SetTile(PS);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 + 1]->SetTile(PS);
		break;
	case Direcciones::Este:
		Tiles[Tiles.size() / 2 - 2][Tiles.at(0).size() - 1]->SetTile(PE);
		Tiles[Tiles.size() / 2][Tiles.at(0).size() - 1]->SetTile(PE);
		Tiles[Tiles.size() / 2 - 1][Tiles.at(0).size() - 1]->SetTile(PE);
		Tiles[Tiles.size() / 2 + 1][Tiles.at(0).size() - 1]->SetTile(PE);
		break;
	case Direcciones::Oeste:
		Tiles[Tiles.size() / 2 - 2][0]->SetTile(PO);
		Tiles[Tiles.size() / 2][0]->SetTile(PO);
		Tiles[Tiles.size() / 2 - 1][0]->SetTile(PO);
		Tiles[Tiles.size() / 2 + 1][0]->SetTile(PO);
		break;
	default:
		break;
	}
}
void Room::abrirPuertas()
{
	for (auto puerta : Puertas)
		puerta->abrirPuerta();
}
void Room::nuevoEnemigo(Objeto * o)
{
	enemigos.push_back(o);
	if (static_cast<Enemigo*>(enemigos.at(enemigos.size() - 1))->killable()) {
		killableEnemies++;
	}
}
void Room::getTileOcupable(SDL_Rect & rect)
{
	srand(SDL_GetTicks());
	int contador = 0;
	int k = rand()%Tiles.size();
	int j = rand() % Tiles[k].size();
	bool flag = true;
	rect.x = Tiles[k][j]->getBox().x;
	rect.y = Tiles[k][j]->getBox().y;
	TilesOcupados(rect,flag);
	while (flag)
	{
		contador++;
		k = rand() % Tiles.size();
		j = rand() % Tiles[k].size();
		rect.x = Tiles[k][j]->getBox().x;
		rect.y = Tiles[k][j]->getBox().y;
		TilesOcupados(rect, flag);
		if (contador > 1000){
			throw exception("no se encuentra una mierda\n");
		}
	}
}
vector<SDL_Point> Room::TilesOcupados(SDL_Rect const recto, bool & Solapa)
{
	vector<SDL_Point> marcados;
	Solapa = false;
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		for (size_t j = 0; j < Tiles.at(i).size(); j++)
		{
			if (Tiles[i][j]->Dentro(recto)) { 
				marcados.push_back({ i, j }); 
				if (!Solapa){
					Solapa = ocupados[i][j];
				}
			}
		}
		
	}
	return marcados;
}

void Room::InitTiles()
{
	TMXReader::Layer * lay = mapdat->getLayer();
	Tiles.reserve(lay->getH());
	int y = area->y;
	for (size_t i = 0; i < Tiles.capacity(); i++)
	{
		int x = area->x;
		Tiles.push_back(vector<Tile*>());
		Tiles[i].reserve(lay->getW());
		for (size_t j = 0; j < mapdat->getW(); j++)
		{
			Tiles[i].push_back(new Tile(x,y,lay->getCell(j,i)-1,pJuego->getWorld()));
			x += TILE_WIDTH;
		}
		y += TILE_HEIGHT;
	}
}

void Room::InitRoom()
{
	InitTiles();
	initPuertas();
	meterEntidades();

}

void Room::meterEntidades(){
	TMXReader::Objectgroup * objg = mapdat->getObjectGroup();
	
	if (objg != nullptr) {
		for (size_t i = 0; i < objg->groupSize(); i++) {
			TMXReader::ObjectInfo * obj = objg->at(i);
			if (obj->getType() == "inanimado") {
				objetos.push_back(creaEntidad(pJuego,obj,area->x,area->y));
				if (objetos.at(objetos.size() - 1) == nullptr)
					objetos.pop_back();
			}
			else if(obj->getType() == "enemigo"){
				
				enemigos.push_back(creaEntidad(pJuego, obj, area->x, area->y));
				
				if (enemigos.at(enemigos.size() - 1) == nullptr)
					enemigos.pop_back();
				//Si el enemigo puede matarse, sumamos uno al índice.
				else if (static_cast<Enemigo*>(enemigos.at(enemigos.size() - 1))->killable()) {
					killableEnemies++;
				}
			}
		}
	}
}

void Room::render(){
	//Dibujamos los tiles de fondo.
	int C;
	SDL_Rect Dibujar;
	int tipoDeTile;
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		bool Racha = false;
		for (size_t j = 0; j < Tiles[i].size(); j++){
			if (Tiles.at(i).at(j)->render(&pJuego->getCameraRect(), Dibujar, tipoDeTile)) {
				if (!Racha)C = i;
				textTiles->draw(pJuego->getRender(), Dibujar, tipoDeTile, pJuego->getCamera());
				Racha = true;
				
			}else if (Racha){
				i = C;
				break;
			}
		}
	}
	//Dibujamos enemigos y objetos.
	for (int i = 0; i < objetos.size(); i++) {
		if (objetos[i]!=nullptr)
			objetos[i]->draw();
	}
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->draw();

	}
	for (int i = 0; i < extras.size(); i++) {
		extras[i]->draw();
	}
}

void Room::encontrarPosicionTiled(int & const x, int & const y, int & posTileX, int & posTileY)
{
	posTileX = (x-area->x)/area->w;
	posTileY = (y - area->y) / area->y;
}

