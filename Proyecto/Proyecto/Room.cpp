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
//No hace falta meter los parametros string para cargar un tilesheet, carga por defecto el de la zona 1
Room::Room(Juego * pJ, vector<Room*> * ro, Zona* z) :pJuego(pJ)
{
	
	zona = z;
	//Si es base, creamos la room de Base
	if (typeid(ZonaBase) == typeid(*zona)){
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
		mapdat = pJuego->getBaseRoom();
		SetRoomFichero(" ", ro);
		ocupados = vector<vector<bool>>(mapdat->getH(), vector<bool>(mapdat->getH(), false));
		for (size_t i = 0; i < ocupados.size(); i++)
		{
			for (size_t j = 0; j < ocupados[i].size(); j++)
			{
				ocupados[i][j] = Tiles[i][j]->getBody() != nullptr;
			}
		}
		meterEntidades();
	
	}
	//Si no, generamos una zona con niveles aleatorios y to la pesca.
	else{
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
		mapdat = pJuego->getRoom();
		SetRoomFichero(" ", ro);
		ocupados = vector<vector<bool>>(Tiles.size(), vector<bool>(Tiles[0].size(), false));
		for (size_t i = 0; i < ocupados.size(); i++)
		{
			for (size_t j = 0; j < ocupados[i].size(); j++)
			{
				ocupados[i][j] = Tiles[i][j]->getBody() != nullptr;
			}
		}
		meterEntidades();
	}
}



//Metodo que se llama cuando se sale de la habitación. Se llama al stop de todos lo enemigos, que tienen que dejar de hacer ataques. **ESTO ES PROVISIONAL**
void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}
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
void Room::setPuertas(int dicc)
{
	Puerta _p;
	switch (dicc)
	{
	case Direcciones::Norte:
		Tiles[0][Tiles.at(0).size() / 2 - 2]->SetTile(ISE);
		Tiles[0][Tiles.at(0).size() / 2]->SetTile(S1);
		Tiles[0][Tiles.at(0).size() / 2 - 1]->SetTile(S1);
		Tiles[0][Tiles.at(0).size() / 2 + 1]->SetTile(ISO);
		_p.posicion = Tiles[0][Tiles.at(0).size() / 2 - 1]->getBox();
		_p.posicion.w = 2*TILE_WIDTH;
		_p.posicion.h = 3 * TILE_HEIGHT;
		_p.DirPuerta = Norte;
		break;
	case Direcciones::Sur:
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 2]->SetTile(INE);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2]->SetTile(S1);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 1]->SetTile(S1);
		Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 + 1]->SetTile(INO);
		_p.posicion = Tiles[Tiles.size() - 1][Tiles.at(0).size() / 2 - 1]->getBox();
		_p.posicion.w = 2 * TILE_WIDTH;
		_p.posicion.h = -3 * TILE_HEIGHT;
		_p.DirPuerta = Sur;
		break;
	case Direcciones::Este:
		Tiles[Tiles.size() / 2 - 2][Tiles.at(0).size() - 1]->SetTile(ISO);
		Tiles[Tiles.size() / 2][Tiles.at(0).size() - 1]->SetTile(S1);
		Tiles[Tiles.size() / 2 - 1][Tiles.at(0).size() - 1]->SetTile(S1);
		Tiles[Tiles.size() / 2 + 1][Tiles.at(0).size() - 1]->SetTile(INO);
		_p.posicion = Tiles[Tiles.size() / 2 - 1][Tiles.at(0).size() - 1]->getBox();
		_p.posicion.w = -3 * TILE_WIDTH;
		_p.posicion.h = 2 * TILE_HEIGHT;
		_p.DirPuerta = Este;
		break;
	case Direcciones::Oeste:
		Tiles[Tiles.size() / 2 - 2][0]->SetTile(ISE);
		Tiles[Tiles.size() / 2][0]->SetTile(S1);
		Tiles[Tiles.size() / 2 - 1][0]->SetTile(S1);
		Tiles[Tiles.size() / 2 + 1][0]->SetTile(INE);
		_p.posicion = Tiles[Tiles.size() / 2 - 1][0]->getBox();
		_p.posicion.w = 3 * TILE_WIDTH;
		_p.posicion.h = 2 * TILE_HEIGHT;
		_p.DirPuerta = Oeste;
		break;
	default:
		break;
	}
	for (size_t i = 0; i < objetos.size(); i++)
	{
		if (SDL_HasIntersection(static_cast<Entidad*>(objetos[i])->getRect(), &_p.posicion)){
			delete objetos[i];
			objetos[i] = nullptr;
		}
			
	}
	Puertas.push_back(_p);
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

void Room::SetRoomFichero(string Dir, vector<Room*> * Habitaciones)
{
	int IniX = 0, IniY = 0;
	int kek = 0;
	TMXReader::Layer * lay = nullptr; 
	mapdat->getLayer(lay);
	if (Habitaciones != nullptr && Habitaciones->size() > 0){
		SDL_Rect _zona = { 0, 0, lay->getW()*TILE_WIDTH, lay->getH()*TILE_HEIGHT };
		Room * _roomConectada;
		Direcciones D;
		SDL_Point _nuevaPos = lazyFoo(solapamientoHabitaciones(Habitaciones,_zona),_roomConectada,D);
		IniX=_nuevaPos.x;
		IniY = _nuevaPos.y;
		_roomConectada->setPuertas(D);
		kek = D;
	}
	int y = IniY;

	Tiles.reserve(lay->getH());
	for (size_t i = 0; i < Tiles.capacity(); i++)
	{
		int x = IniX;
		Tiles.push_back(vector<Tile*>());
		Tiles[i].reserve(lay->getW());
		for (size_t j = 0; j < mapdat->getW(); j++)
		{
			Tiles[i].push_back(new Tile(x,y,lay->getCell(j,i)-1,pJuego->getWorld()));
			x += TILE_WIDTH;
		}
		y += TILE_HEIGHT;
	}
	
	area = new SDL_Rect{ IniX , IniY, lay->getW()*TILE_WIDTH, lay->getH()*TILE_HEIGHT};
	if (kek != 0)
		setPuertas(-kek);
}

void Room::meterEntidades(){
	TMXReader::Objectgroup * objg = nullptr;
	mapdat->getObjectGroup(objg);
	if (objg != nullptr) {
		for (size_t i = 0; i < objg->groupSize(); i++) {
			TMXReader::ObjectInfo * obj = objg->operator[](i);
			if (obj->getType() == "inanimado") {
				objetos.push_back(creaEntidad(pJuego,obj,area->x,area->y));
				if (objetos.at(objetos.size() - 1) == nullptr)
					objetos.pop_back();
			}
			else if(obj->getType() == "enemigo"){
				enemigos.push_back(creaEntidad(pJuego, obj, area->x, area->y));
				if (enemigos.at(enemigos.size() - 1) == nullptr)
					enemigos.pop_back();
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

