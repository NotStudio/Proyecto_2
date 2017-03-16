#ifndef ROOM_H_
#define ROOM_H_
#include "Juego.h"
#include "Tile.h"
#include "TileInfo.h"
#include "Bala.h"
class Room
{
private:
	Room * Norte = nullptr;
	Room * Sur = nullptr;
	Room * Este = nullptr;
	Room * Oeste = nullptr;
	int x, y;
	//la zona de la room
	SDL_Rect * area;
	Juego * pJuego;
	Tilesheet * textTiles;
	//el vector de los tiles
	vector<vector<Tile*>> Tiles;
	vector<vector<bool>> ocupados;
	
	Puerta Entrada;
	Puerta Salida;
	int ANCHO_NIVEL, ALTO_NIVEL;
	void moverMapa(int desplazamientoX, int desplazamientoY);
	bool setTiles(string d,b2World* Wardo);
	void getTileOcupable(SDL_Rect &);
	//Vector de enemigos.
	vector<Objeto*> enemigos;
	//Vector de objetos inanimados.
	vector<Objeto*> objetos;
	//Dificultad.(int, struct)
	vector<Objeto*> extras;//Balas
	void ColocarHabitacion(vector<Room*> *habitaciones);
	void marcarOcupados(vector<SDL_Point>const );
	vector<Direcciones> puertas;
	void setPuertas(Direcciones dicc);
public:
	size_t numPuertas() { return puertas.size(); }
	void nuevaBala(Bala*bala){
		extras.push_back(bala);
	}
	bool dentroRoom(SDL_Point* box) {
		return !(area->x > box->x || area->x + area->w < box->x || area->y > box->y || area->y + area->h < box->y);
	}
	bool dentroRoom(SDL_Rect box) {
		return !(area->x >= box.x + box.w || area->x + area->w <= box.x || area->y >= box.y + box.h || area->y + area->h <= box.y);
	}
	Puerta getSalida() {
		return Salida;
	}
	//para saber las puertas donde estan
	SDL_Rect getArea() {
		return *area;
	}
	void update();
	//Room();
	Room(Juego *,Puerta Salida, vector<Room*>*,Puerta * Entrada = nullptr,int x=0, int y=0,string a = "tilesheet",string b="zon1");
	~Room();
	void DestroyRoom(b2World * wardo);
	int getAnchoRoom()const { return ANCHO_NIVEL; }
	int getAltoRoom()const { return ALTO_NIVEL; }
	void render();
	int encontrarPosicionTiled(int & const x, int & const y);
	vector<SDL_Point> TilesOcupados(SDL_Rect const recto, bool & a );
	void SetRoomFichero(string Dir);
	void stop();
	void meterInanimados(string const dir);
	

}; // !1
#endif // !ROOM_H_