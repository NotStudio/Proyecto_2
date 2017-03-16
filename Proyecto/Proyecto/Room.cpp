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
Room::Room(Juego * pJ, Puerta sal, vector<Room*> const & ro, Puerta * entrada, int x, int y, string a, string b) :pJuego(pJ)
{
	textTiles = new Tilesheet(24, pJuego->getTextura(a, b));
	a = (entrada == nullptr || entrada->zonaPuerta.w == 1024) ? "../Material/Maps/mapaGrande.csv" : "../Material/Maps/mapa_Peque.map";
	Tiles = RoomDesdeArchivo(a, pJuego->getWorld());
	area = new SDL_Rect{Tiles[0][0]->getBox().x, Tiles[0][0]->getBox().y, Tiles.at(0).size()*TILE_WIDTH, Tiles.size()*TILE_HEIGHT};
	if(entrada != nullptr){

	}
	ocupados = vector<vector<bool>>(Tiles.size(),vector<bool>(Tiles[0].size(),false));
	for (size_t i = 0; i < ocupados.size(); i++)
	{
		for (size_t j = 0; j < ocupados[i].size(); j++)
		{
			ocupados[i][j] = Tiles[i][j]->getBody()!=nullptr;
		}
	}
	ColocarHabitacion(ro);
	//setTiles(DirM, wardo);
	//Salida.zonaPuerta = *area;
	int xp = 0, yp = 0;
	//meterInanimados("a");
	/*
	//Crear el vector de objetos, leer de archivos.
	//Crear vector de enemigos.
	//enemigos.push_back(new Perseguidor(pJuego, SDL_Rect{ area->w / 2 + area->x, area->h /2 + area->y , 64,64 }));
	enemigos.push_back(new EnemigoBomba(pJuego, Tiles->at(getTileOcupable())->getBox()));
	enemigos.push_back(new EnemigoBomba(pJuego, Tiles->at(getTileOcupable())->getBox()));
	enemigos.push_back(new MaquinaDePelotas(pJuego, SDL_Rect{ area->w / 2 + TILE_WIDTH *4 + area->x, area->h /2 +TILE_HEIGHT*4 + area->y , 128,128 }));
	enemigos.push_back(new Perseguidor(pJuego, SDL_Rect{ 500 + area->x,  500 + area->y , 64,64}));
	*/
}

void Room::ColocarHabitacion(vector<Room*>const & Habitaciones){
	if (Habitaciones.size() >= 1){
		
	}
	else{
		Salida.DirPuerta = Direcciones(rand() % Sinsitio);
		Salida.DirPuerta = Direcciones::Este;
		switch (Salida.DirPuerta)
		{
		case Direcciones::Norte:
			break;
		case Direcciones::Sur:
			break;
		case Direcciones::Oeste:
			Tiles[Tiles.size() / 2 -2][Tiles.size() - 1]->SetTile(ISO);
			Tiles[Tiles.size() / 2][Tiles.size()-1]->SetTile(S1);
			Tiles[Tiles.size() / 2 -1][Tiles.size()-1]->SetTile(S1);
			Tiles[Tiles.size() / 2 + 1][Tiles.size() - 1]->SetTile(INO);
			Salida.posicion = Tiles[Tiles.size() / 2 - 1][Tiles.size() - 1]->getBox();
			Salida.posicion.h += TILE_HEIGHT;
			break;
		case Direcciones::Este:
			Tiles[Tiles.size() / 2 - 2][0]->SetTile(ISE);
			Tiles[Tiles.size() / 2][0]->SetTile(S1);
			Tiles[Tiles.size() / 2 - 1][0]->SetTile(S1);
			Tiles[Tiles.size() / 2 + 1][0]->SetTile(INE);
			Salida.posicion = Tiles[Tiles.size() / 2-1][0]->getBox();
			Salida.posicion.h += TILE_HEIGHT;
			Salida.posicion.w += TILE_WIDTH*2;
			break;
		default:
			break;
		}
		bool aux;
		marcarOcupados(TilesOcupados(Salida.posicion, aux));
	}
}

//Metodo que se llama cuando se sale de la habitación. Se llama al stop de todos lo enemigos, que tienen que dejar de hacer ataques. **ESTO ES PROVISIONAL**
void Room::stop() {

	for (int i = 0; i < enemigos.size(); i++) {
		static_cast<Enemigo*>(enemigos[i])->stop();
	}
}

void Room::meterInanimados(string const dir)
{
	ifstream fichero("manolo.txt");
	string linea;
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
				objetos.push_back(creaInanimado(pJuego, tipo, posX*TILE_WIDTH-area->x, posY*TILE_HEIGHT-area->y, escala));
			}
			catch (const std::exception&)
			{
				cout << "Ese objeto no existe parguelas \n";
			}
		}
		getline(fichero, linea);
	}while (!fichero.fail());
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


void Room::SetRoomFichero(string Dir)
{
//	RoomDesdeArchivo(Dir, pJuego->getWorld(), ANCHO_NIVEL, ALTO_NIVEL);
}
*/
void Room::render(){
	//Dibujamos los tiles de fondo.
	SDL_Rect Dibujar;
	int tipoDeTile;
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		bool Racha = false;
		for (size_t j = 0; j < Tiles[i].size(); j++){
			if (Tiles.at(i).at(j)->render(&pJuego->getCameraRect(), Dibujar, tipoDeTile)) {
				textTiles->draw(pJuego->getRender(), Dibujar, tipoDeTile, pJuego->getCamera());
				Racha = true;
#ifdef DEBUG
				if (ocupados[i][j]) {
					Dibujar.x -= pJuego->getCameraRect().x;
					Dibujar.y -= pJuego->getCameraRect().y;
					SDL_RenderDrawRect(pJuego->getRender(), &Dibujar);
				}
#endif // DEBUG
			}
			else if (Racha){
				Racha = false;
				break;
			}
		}

	}
	//Dibujamos enemigos y objetos.
	for (int i = 0; i < objetos.size(); i++) {
		objetos[i]->draw();
	}
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->draw();
#ifdef DEBUG
		SDL_Point a = pJuego->getCamera()->getPosRelativa(*static_cast<Entidad*>(enemigos[i])->getRect()), b = pJuego->getCamera()->getPosRelativa(pJuego->getCamera()->getTarget());
		SDL_RenderDrawLine(pJuego->getRender(), b.x, b.y, a.x, a.y);
#endif // DEBUG

	}
	for (int i = 0; i < extras.size(); i++) {
		extras[i]->draw();
	}
}

