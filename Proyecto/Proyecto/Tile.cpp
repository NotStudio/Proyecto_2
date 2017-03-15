#include "Tile.h"
#include "TileInfo.h"
#include "Juego.h"
#include "checkML.h"
void Tile::onColisionEnter() { }
Tile::Tile(int x, int y, int tileType, b2World * wardo)
{

	mBox = new SDL_Rect{ x,y,TILE_WIDTH,TILE_HEIGHT };
	mType = tileType;
	if (mType > S12) {
		mBodyDef = new b2BodyDef;
		mBodyDef->position.Set((float32)mBox->x, (float32)mBox->y);
		mBodyDef->type = b2_staticBody;
		mBodyDef->active = true;
		mBody = wardo->CreateBody(mBodyDef);
		mShapeDef = new b2FixtureDef;
		mShape = new b2PolygonShape();
		b2Vec2 Puntos[4];
		Puntos[0] = b2Vec2(0, 0);
		Puntos[1] = b2Vec2(0, TILE_HEIGHT);
		Puntos[2] = b2Vec2(TILE_WIDTH, TILE_HEIGHT);
		Puntos[3] = b2Vec2(TILE_WIDTH, 0);
		mShape->Set(Puntos, 4);
		mShapeDef->shape = mShape;
		mBody->CreateFixture(mShapeDef);
		mBody->SetUserData(this);
	}
	else {

	}
}
Tile::~Tile()
{
	delete mBox;
	mBox = nullptr;
	if (mType > S12) {
		delete mShape;
		delete mShapeDef;
		delete mBodyDef;

		mShapeDef = nullptr;
		mShape = nullptr;
		mBodyDef = nullptr;
	}
}
SDL_Rect  Tile::getBox() {
	return *mBox;
}
void Tile::setPos(float32 x, float32 y) {
	mBox->x = mBody->GetPosition().x;
	mBox->y = mBody->GetPosition().y;
}
int Tile::getType() {
	return mType;
}
bool Tile::render(SDL_Rect * camara, SDL_Rect& rectangulo, int & tipo) {
	rectangulo = getBox();
	tipo = getType();
	return Dentro(camara);
}
bool Tile::Dentro(SDL_Rect*box)const
{
	return !(mBox->x > box->x + box->w || mBox->x + mBox->w < box->x || mBox->y > box->y + box->h || mBox->y + mBox->h < box->y);
}
b2Body * Tile::getBody()
{
	return mBody;
}

void Tile::SetTile(int newType)
{
	mType = newType;
	if (mType < S12) {
		delete mShape;
		delete mShapeDef;
		delete mBodyDef;
		mBody = nullptr;
		mShapeDef = nullptr;
		mShape = nullptr;
		mBodyDef = nullptr;
	}
}

