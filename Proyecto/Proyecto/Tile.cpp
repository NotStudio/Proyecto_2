#include "Tile.h"
#include "TileInfo.h"
#include "Juego.h"
#include "checkML.h"

void Tile::onColisionEnter() {}
Tile::Tile(int x, int y, int tileType, b2World * wardo)
{

	mBox = new SDL_Rect{ x,y,TILE_WIDTH,TILE_HEIGHT };
	mType = tileType;
	if (mType > S12) {
		float32 fx = x, fy=y;
		b2FixtureDef mShapeDef;
		b2PolygonShape mShape;
		b2BodyDef mBodyDef;
		mBodyDef = b2BodyDef();
		mBodyDef.position.Set((float32)fx / PPM, (float32)fy / PPM);
		mBodyDef.type = b2_staticBody;
		mBodyDef.active = true;
		mBody = wardo->CreateBody(&mBodyDef);
		mShapeDef = b2FixtureDef();
		mShape = b2PolygonShape();
		b2Vec2 Puntos[4];
		Puntos[0] = b2Vec2(0.0F, 0.0F);
		Puntos[1] = b2Vec2(0.0F, TILE_HEIGHT_F / PPM);
		Puntos[2] = b2Vec2(TILE_WIDTH_F / PPM, TILE_HEIGHT_F / PPM);
		Puntos[3] = b2Vec2(TILE_WIDTH_F / PPM, 0.0F);
		mShape.Set(Puntos, 4);
		mShapeDef.shape = &mShape;
		mShapeDef.filter.categoryBits = Juego::ESCENARIO;
		mShapeDef.filter.maskBits = -1;
		mBody->CreateFixture(&mShapeDef);
		mBody->SetUserData(this);
	}
	else {

	}
}
Tile::~Tile()
{
	delete mBox;
	mBox = nullptr;
	if (mBody!=nullptr) {
		mBody->SetUserData(nullptr);
		mBody->GetWorld()->DestroyBody(mBody);
		
	}
}
SDL_Rect  Tile::getBox() {
	return *mBox;
}
void Tile::setPos(float32 x, float32 y) {
	mBox->x += x;
	mBox->y += y;
	if(mBody!=nullptr)
		mBody->SetTransform(b2Vec2(mBox->x / PPM, mBox->y / PPM), 0);
}
int Tile::getType() {
	return mType;
}
bool Tile::render(SDL_Rect * camara, SDL_Rect& rectangulo, int & tipo) {
	rectangulo = getBox();
	tipo = getType();
	return Dentro(*camara);
}
bool Tile::Dentro(SDL_Rect box)const
{
	return !(mBox->x >= box.x + box.w || mBox->x + mBox->w <= box.x || mBox->y >= box.y + box.h || mBox->y + mBox->h <= box.y);
}
b2Body * Tile::getBody()
{
	return mBody;
}

void Tile::SetTile(int newType)
{
	mType = newType;
	if (mType <=S12 && mBody!=nullptr) {
		mBody->SetActive(false);
	}else if(mBody!= nullptr){
		mBody->SetActive(true);
	}

}

