#include "Room.h"
#include "TileInfo.h"
void Tile::onColisionEnter() { cout << "kek"; }
Tile::Tile(int x, int y, int tileType, b2World * wardo)
{

	mBox = new SDL_Rect{ x,y,TILE_WIDTH,TILE_HEIGHT };
	mType = tileType;
	if (mType > 2) {
		mBodyDef = new b2BodyDef;
		mBodyDef->position.Set((float32)mBox->x, (float32)mBox->y);
		mBodyDef->type = b2_staticBody;
		mBodyDef->active = true;
		mBody = wardo->CreateBody(mBodyDef);
		mShapeDef = new b2FixtureDef;
		mShape = new b2PolygonShape();
		mShape->SetAsBox((float32)TILE_WIDTH / 2, (float32)TILE_HEIGHT / 2);
		mShapeDef->shape = mShape;
		mBody->CreateFixture(mShapeDef);
	}
	else {

	}
}
Tile::~Tile()
{
	delete mBox;
	mBox = nullptr;
	if (mType > 2) {
		delete mShape;
		delete mShapeDef;
		delete mBodyDef;
		mBody = nullptr;

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
void Tile::render() {
}
bool Tile::Dentro(SDL_Rect*box)const
{
	return !(mBox->x > box->x + box->w || mBox->x + mBox->w < box->x || mBox->y > box->y + box->h || mBox->y + mBox->h < box->y);
}
b2Body * Tile::getBody()
{
	return mBody;
}

