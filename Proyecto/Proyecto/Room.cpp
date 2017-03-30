#include <fstream>                        
#include<stdio.h>
#include "Room.h"
#include "checkML.h"
#include "constructoraRooms.h"
#include "Perseguidor.h"
#include "EnemigoBomba.h"
#include "MaquinaDePelotas.h"
#include "Inanimado.h"
#include "InanimadoInfo.h"
#include "TileInfo.h"
#include <time.h>
#include "Sierra.h"
#include "Helice.h"
#include "ZonaBase.h"
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
	//Si es base, creamos la room de Base.
	if (typeid(ZonaBase) == typeid(*zona)){
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
		RoomInfo _infoRoom = pJuego->getBaseRoom();
		cout << _infoRoom.fichero() << "\n";
		SetRoomFichero(_infoRoom.fichero(), ro);
		ocupados = vector<vector<bool>>(Tiles.size(), vector<bool>(Tiles[0].size(), false));
		for (size_t i = 0; i < ocupados.size(); i++)
		{
			for (size_t j = 0; j < ocupados[i].size(); j++)
			{
				ocupados[i][j] = Tiles[i][j]->getBody() != nullptr;
			}
		}
	
	
	}
	//Si no, generamos una zona con niveles aleatorios y to la pesca.
	else{
		textTiles = new Tilesheet(TOTAL_TILES, pJuego->getTilesheet(zona));
		RoomInfo _infoRoom = pJuego->getRoom();
		cout << _infoRoom.fichero() << "\n";
		SetRoomFichero(_infoRoom.fichero(), ro);
		ocupados = vector<vector<bool>>(Tiles.size(), vector<bool>(Tiles[0].size(), false));
		for (size_t i = 0; i < ocupados.size(); i++)
		{
			for (size_t j = 0; j < ocupados[i].size(); j++)
			{
				ocupados[i][j] = Tiles[i][j]->getBody() != nullptr;
			}
		}
		meterInanimados(_infoRoom.PatronObjetos());
		//meterEnemigos(_infoRoom.PatronEnemigos());
		enemigos.push_back(new Perseguidor(pJuego, 200, 200));
	}
}



//Metodo que se llama cuando se sale de la habitación. Se llama al stop de todos lo enemigos, que tienen que dejar de hacer ataques. **ESTO ES PROVISIONAL**
void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}
}


void Room::meterInanimados(string const &dir)
{
	ifstream fichero(dir);
	string linea;
	int i=0;
	getline(fichero, linea);
	do
	{
		
		string tipo = "";
		int posX = -1,posY=-1;
		float escala = 1;
		stringstream _lectorLineas(linea);
		_lectorLineas >> tipo >> posX >> posY >> escala;
		if (tipo != "") {
			try
			{
				objetos.push_back(creaInanimado(pJuego, tipo, area->x + posX*TILE_WIDTH, area->y + posY*TILE_HEIGHT, escala));
				bool solapa = false;
				vector<SDL_Point> _TOcupados = TilesOcupados(*static_cast<Entidad*>(objetos[i])->getRect(), solapa);
				marcarOcupados(_TOcupados);
				i++;

			}
			catch (const std::exception& e)
			{
				cout <<e.what();
			}
		}
		getline(fichero, linea);
	}while (!fichero.fail());
	fichero.close();

}
void Room::meterEnemigos(string const & dir){
	ifstream fichero(dir);
	string linea;
	getline(fichero, linea);
	int i = 0;
	do
	{
		
		string tipo = "";
		int posX = -1, posY = -1;
		int aditional = 1;
		stringstream _lectorLineas(linea);
		_lectorLineas >> tipo >> posX >> posY >> aditional;
		if (tipo != ""&&!ocupados[posY][posX]) {
			try
			{
				enemigos.push_back(creaEnemigo(pJuego, tipo, area->x + posX*TILE_WIDTH, area->y + posY*TILE_HEIGHT, aditional));
				bool solapa = false;
				vector<SDL_Point> _TOcupados = TilesOcupados(*static_cast<Entidad*>(enemigos[i])->getRect(), solapa);
				marcarOcupados(_TOcupados);
				i++;
			}
			catch (std::exception&e)
			{
				cout << e.what();
			}
		}
		getline(fichero, linea);
	} while (!fichero.fail());
	fichero.close();
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

//COSAS DE FRAN
// --------------------------------------------------------------------------------------------------------------
/*

bool Room::setTiles(string Dirm,b2World * wardo) {
	
	int x = 0;
	int y = 0;
	return true;
}



void Room::DestroyRoom(b2World * wardo)
{
	for (size_t i = 0; i < Tiles->size(); i++)
	{
			wardo->DestroyBody(Tiles->at(i)->getBody());
	}
}


int Room::encontrarPosicionTiled(int& const x, int& const y)
{
	return(ANCHO_NIVEL / TILE_WIDTH)*((y - (y%TILE_HEIGHT))-1)/TILE_HEIGHT+(1 + (x - (x%TILE_WIDTH)) / TILE_WIDTH);
}

*/
void Room::SetRoomFichero(string Dir, vector<Room*> * Habitaciones)
{
	int IniX = 0, IniY = 0;
	int x = 0, y = 0, tipo = -1, maxX = 0, acuX = 0, acuY = 0, maxY = 0;
	
	
	string linea;
	ifstream mapAux(Dir);
	getline(mapAux, linea);






	stringstream Cuenta(linea);
	do
	{
		char aux;
		int auxy = -20;
		Cuenta >> auxy >> aux;
		if (auxy != -20) acuX++;
	} while (!Cuenta.fail());
	maxX = acuX;
	acuY++;
	do
	{
		getline(mapAux, linea);
		if(!mapAux.fail())acuY++;
	} while (!mapAux.fail());
	mapAux.close();
	maxY = acuY;
	int kek = 0;
	if (Habitaciones != nullptr && Habitaciones->size() > 0){
		SDL_Rect _zona = { 0, 0, maxX*TILE_WIDTH, maxY*TILE_HEIGHT };
		Room * _roomConectada;
		Direcciones D;
		SDL_Point _nuevaPos = lazyFoo(solapamientoHabitaciones(Habitaciones,_zona),_roomConectada,D);
		IniX=_nuevaPos.x;
		IniY = _nuevaPos.y;
		_roomConectada->setPuertas(D);
		kek = D;
	}
	ifstream map(Dir);

	acuY = 0;
	y = IniY;
	getline(map, linea);
	for (size_t i = 0;!map.fail(); i++)
	{
		x = IniX;
		char aux;
		stringstream lee(linea);
		acuX = 0;
		if (!lee.fail()) {
			Tiles.push_back(vector<Tile*>());
			Tiles[acuY].reserve(28);
		}
		do
		{
			lee >> tipo >> aux;
			if (tipo >= 0 && tipo < TOTAL_TILES) {
				Tiles[acuY].push_back(new Tile(x, y, tipo, pJuego->getWorld()));
			}
			x += TILE_WIDTH;
			acuX++;
		} while (!lee.fail());
		(acuX > maxX) ? maxX = acuX : maxX;
		y += TILE_HEIGHT;
		acuY++;
		getline(map, linea);
	}
	map.close();
	area = new SDL_Rect{ IniX , IniY, maxX*TILE_WIDTH, maxY*TILE_HEIGHT};
	if (kek != 0)
		setPuertas(-kek);
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

