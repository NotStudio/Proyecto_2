#ifndef ROOM_H_
#define ROOM_H_
#include "Juego.h"
#include "Tile.h"
#include "TileInfo.h"
#include "Bala.h"
#include "Zona.h"
#include "Puertas.h"
class Room
{
private:
	enum RoomState
	{
		ABIERTA,CERRADA
	}RoomState_;
	
	SDL_Rect * area;
	//la zona de la room
	Juego * pJuego;
	Tilesheet * textTiles;
	//el vector de los tiles
	vector<Puerta*> Puertas;
	vector<vector<Tile*>> Tiles;
	vector<vector<bool>> ocupados;
	
	TMXReader::MapData * mapdat;

	void getTileOcupable(SDL_Rect &);
	//Vector de enemigos.
	vector<Objeto*> enemigos;
	//Vector de objetos inanimados.
	vector<Objeto*> objetos;
	//Dificultad.(int, struct)
	vector<Objeto*> extras;//Balas
	void ColocarHabitacion(vector<Room*> *habitaciones);
	void marcarOcupados(vector<SDL_Point>const );
	vector<SDL_Point> TilesOcupados(SDL_Rect const recto, bool & a);
	vector<vector<bool>> getOcupados() { 
		return ocupados;
	}
	Zona* zona;
	
	bool isEmpty_;
	bool open_;
	int killableEnemies;
	void checkAliveEnemies(int);

public:
	vector<Objeto*> getEnemigos(){
		return enemigos;
	};

	int getNumPuertas() {
		return Puertas.size();
	}
	void setPuertas(Direcciones dicc);
	void initPuertas();
	void cerrarPuertas();
	void cerrarPuerta(int dicc);
	void abrirPuertas();
	void abrirPuerta(int dicc);
	void nuevaBala(Objeto*bala){
		extras.push_back(bala);
	}
	void nuevoObjeto(Objeto* o){
		extras.push_back(o);
	}
	void nuevoEnemigo(Objeto* o); 
	bool dentroRoom(SDL_Point* box) {
		return !(area->x > box->x || area->x + area->w < box->x || area->y > box->y || area->y + area->h < box->y);
	}
	bool dentroRoom(SDL_Rect box) {
		return !(area->x >= box.x + box.w || area->x + area->w <= box.x || area->y >= box.y + box.h || area->y + area->h <= box.y);
	}
	//para saber las puertas donde estan
	SDL_Rect * getArea() {
		try
		{
			if (!this)
				throw new exception();
			else
				return area;
		}
		catch (...)
		{
			throw new exception("Area");
		}
	}
	//Para reanudar tras el pause.
	void resume();
	void update();
	//Room();
	Room(Juego *, Zona *, TMXReader::MapData* mapData_,SDL_Point);
	~Room();
	void render();
	void encontrarPosicionTiled(int & const x, int & const y,int & posTileX,int &posTileY);
	
	void InitTiles();
	void InitRoom();
	void stop();
	void meterEntidades();
	bool isEmpty() { return isEmpty_; }
private:
}; // !1
#endif // !ROOM_H_