#ifndef ROOM_H_
#define ROOM_H_


#include "Juego.h"
#include "TexturasSDL.h"
#include "Camara.h"
class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int tileType,b2World*wardo);
	~Tile();
	//Shows the tile
	void render();

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
	SDL_Renderer * pRend;
	TexturasSDL * kek;
	vector <SDL_Rect*> TileSheetRect;
	vector<Tile*>* Tiles;

	int ANCHO_NIVEL, ALTO_NIVEL;
	
	bool setTiles(string d,b2World* Wardo);
public:
	Room(string direccionMapa, TexturasSDL * t, SDL_Renderer*k, b2World*w);
	Room() ;
	~Room();
	void DestroyRoom(b2World * wardo);
	int getAnchoRoom()const { return ANCHO_NIVEL; }
	int getAltoRoom()const { return ALTO_NIVEL; }
	void render(Camara* camara);
	int encontrarPosicionTiled(int & const x, int & const y);
	vector<int> TilesOcupados(SDL_Rect & const recto);

	

}; // !1
#endif // !ROOM_H_