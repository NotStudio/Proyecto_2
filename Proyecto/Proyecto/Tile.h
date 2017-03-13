#ifndef TILE_H_
#define TILE_H_

#include <Box2D\Box2D.h>
#include <SDL.h>
#include "Objeto.h"
class Tile
{
public:
	//Constructor de Tile
	Tile(int x, int y, int tileType, b2World*world);
	~Tile();
	//devuelve si se puede pintar o no
	bool render(SDL_Rect*, SDL_Rect&, int&);
	void onColisionEnter();
	//devuelve el tipo del tile
	int getType();

	//devuelve el rectangulo del tile
	SDL_Rect getBox();
	//para saber si algo esta dentro del tile
	bool Dentro(SDL_Rect * box)const;
	//para poder borrar el body de un tile si lo tiene
	b2Body * getBody();
	void SetTile(int newType);
	void update();
	void setPos(float32 x, float32 y);
	void* k;
private:
	b2Body * mBody;
	//The attributes of the tile
	SDL_Rect * mBox;
	b2FixtureDef * mShapeDef;
	b2PolygonShape * mShape;

	//The tile type
	int mType=-1;
	b2BodyDef * mBodyDef;
};
#endif // !TILE_H_
