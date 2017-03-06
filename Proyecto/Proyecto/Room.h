#ifndef ROOM_H_
#define ROOM_H_
#include "Juego.h"
#include "TileInfo.h"
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType,b2World*wardo);
	~Tile();
	//Shows the tile
	bool render(SDL_Rect*,SDL_Rect&,int&);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();
	bool Dentro(SDL_Rect * box)const;
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
	int x, y;
	SDL_Rect * area;
	Juego * pJuego;
	vector <SDL_Rect*> TileSheetRect;
	vector<Tile*>* Tiles;
	Direcciones Locport;
	int ANCHO_NIVEL, ALTO_NIVEL;
	
	bool setTiles(string d,b2World* Wardo);
	bool dentroRoom(SDL_Point* box) {
		return !(area->x > box->x || area->x + area->w < box->x || area->y > box->y || area->y + area->h < box->y);
	}
public:
	SDL_Rect getArea() {
		return *area;
	}
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