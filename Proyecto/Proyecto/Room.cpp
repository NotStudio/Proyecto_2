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
//#define DEBUG

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
Room::Room(Juego * pJ,Puerta sal, Puerta * entrada,int x, int y,string a ,string b ) :pJuego(pJ)
{
	textTiles = new Tilesheet(24, pJuego->getTextura(a,b));
	a = (entrada==nullptr||entrada->zonaPuerta.w==1024)? "../Material/Maps/mapa_Grande.map": "../Material/Maps/mapa_Peque.map";
	Tiles = new vector<Tile*>(RoomDesdeArchivo(a,pJuego->getWorld(),ANCHO_NIVEL,ALTO_NIVEL,sal,entrada));
	ocupados = vector<bool>(Tiles->size(), false);
	for (size_t i = 0; i < ocupados.size(); i++)
	{
		ocupados[i] = Tiles->at(i)->getBody()==nullptr;
	}
	//setTiles(DirM, wardo);
	Salida = sal;
	area = new SDL_Rect{ Tiles->at(0)->getBox().x ,Tiles->at(0)->getBox().y,ANCHO_NIVEL,ALTO_NIVEL };
	Salida.zonaPuerta = *area;
	int xp = 0, yp = 0;
	//meterInanimados("a");

	//Crear el vector de objetos, leer de archivos.
	if (entrada == nullptr) {
		objetos.push_back(new Agujero(pJuego, SDL_Point{ TILE_WIDTH * 3 + area->x, area->w / 2 + TILE_HEIGHT * 7 + area->y }, 150));
		objetos.push_back(new Nave(pJuego, SDL_Point{ area->w - TILE_WIDTH * 5 + area->x, TILE_HEIGHT * 3 + area->y }, TILE_WIDTH * 3));
		objetos.push_back(new Chatarra(pJuego, SDL_Point{ TILE_WIDTH * 1 + area->x, area->w / 2 + TILE_HEIGHT + area->y }, TILE_WIDTH / 4));
		objetos.push_back(new Chatarra(pJuego, SDL_Point{ TILE_WIDTH * 2 + area->x, area->w / 2 + TILE_HEIGHT * 2 + area->y }, TILE_WIDTH / 4));
		objetos.push_back(new Tuberia(pJuego, SDL_Point{ TILE_WIDTH / 2 + area->x, area->w / 2 + TILE_HEIGHT * 7 + area->y }, TILE_WIDTH / 2));
	}
	for (size_t i = 0; i < objetos.size(); i++)
	{
		vector<int>marcados = TilesOcupados(*static_cast<Entidad*>(objetos[i])->getRect());
		for (size_t i = 0; i < marcados.size(); i++)
		{
			ocupados[marcados[i]]=false;
		}
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
				objetos.push_back(creaInanimado(pJuego, tipo, posX*TILE_WIDTH-area->x , posY*TILE_HEIGHT-area->y, escala));
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
	while (ocupados[k])
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
			#ifdef DEBUG
			 if (!ocupados[i]) {
				 Dibujar.x -= pJuego->getCameraRect().x;
				 Dibujar.y -= pJuego->getCameraRect().y;
				 SDL_RenderDrawRect(pJuego->getRender(), &Dibujar);
			 }
			#endif // DEBUG
		}

	}
	//Dibujamos enemigos y objetos.
	for (int i = 0; i < objetos.size(); i++) {
		objetos[i]->draw();
	}
	for (int i = 0; i < enemigos.size(); i++) {
		enemigos[i]->draw();
	#ifdef DEBUG
		SDL_Point a = pJuego->getCamera()->getPosRelativa(*static_cast<Entidad*>(enemigos[i])->getRect()), b= pJuego->getCamera()->getPosRelativa(pJuego->getCamera()->getTarget());
		SDL_RenderDrawLine(pJuego->getRender(), b.x, b.y, a.x, a.y);
	#endif // DEBUG

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
	vector<int>marcados;
	for (int i = 0; i < Tiles->size(); i++)
	{
		if (Tiles->at(i)->Dentro(recto)) marcados.push_back(i);
	}
	return marcados;
}

void Room::SetRoomFichero(string Dir)
{
//	RoomDesdeArchivo(Dir, pJuego->getWorld(), ANCHO_NIVEL, ALTO_NIVEL);
}


