#ifndef ROOM_H_
#define ROOM_H_
#include "Juego.h"
#include "TileInfo.h"
class Tile
{
public:
	//Constructor de Tile
	Tile(int x, int y, int tileType,b2World*world);
	~Tile();
	//devuelve si se puede pintar o no
	bool render(SDL_Rect*,SDL_Rect&,int&);

	//devuelve el tipo del tile
	int getType();

	//devuelve el rectangulo del tile
	SDL_Rect getBox();
	//para saber si algo esta dentro del tile
	bool Dentro(SDL_Rect * box)const;
	//para poder borrar el body de un tile si lo tiene
	b2Body * getBody();
	void setPos(float32 x, float32 y);
private:

	void onColisionEnter();
	b2Body * mBody;
	//The attributes of the tile
	SDL_Rect * mBox;
	b2FixtureDef * mShapeDef;
	b2PolygonShape * mShape;

	//The tile type
	int mType;
	b2BodyDef * mBodyDef;
};
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
	vector <SDL_Rect*> TileSheetRect;
	//el vector de los tiles
	vector<Tile*>* Tiles;
	Direcciones Locport;
	int ANCHO_NIVEL, ALTO_NIVEL;
	
	bool setTiles(string d,b2World* Wardo);
	
	//Vector de enemigos.
	vector<Objeto*> enemigos;
	//Vector de objetos inanimados.
	//Dificultad.(int, struct)


public:
	bool dentroRoom(SDL_Point* box) {
		return !(area->x > box->x || area->x + area->w < box->x || area->y > box->y || area->y + area->h < box->y);
	}
	//para saber las puertas donde estan
	Room * getRoomNorte() { return Norte; }
	Room * getRoomSur() { return Sur; }
	Room * getRoomEste() { return Este; }
	Room * getRoomOeste() { return Oeste; }
	Direcciones getPuertas() { return Locport; }
	SDL_Rect getArea() {
		return *area;
	}
	void SetRoom(Direcciones p);
	void update();
	//Room();
	Room(Juego *,int x, int y,Direcciones);
	~Room();
	void DestroyRoom(b2World * wardo);
	int getAnchoRoom()const { return ANCHO_NIVEL; }
	int getAltoRoom()const { return ALTO_NIVEL; }
	void render();
	int encontrarPosicionTiled(int & const x, int & const y);
	vector<int> TilesOcupados(SDL_Rect & const recto);
	void SetRoomFichero(string Dir);

	

}; // !1
#endif // !ROOM_H_