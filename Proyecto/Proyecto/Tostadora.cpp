#include "Tostadora.h"
#include "Bala.h"
#include "Play.h"
#include "checkML.h"

Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	//Física
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	bodyDef.fixedRotation=true;
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	/*
	b2Vec2 Puntos[4];
	Puntos[0] = b2Vec2(0, 32);
	Puntos[1] = b2Vec2(0, 64);
	Puntos[2] = b2Vec2(64, 64);
	Puntos[3] = b2Vec2(64, 32);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->Set(Puntos, 4);
	*/
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, {(float)sprite->w/2, (float)sprite->h/2},0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	//Capa de colision.
	fDef.filter.categoryBits = Juego::JUGADOR;
	fDef.filter.maskBits = Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::ITEM | Juego::ESCENARIO;
	body->CreateFixture(&fDef);
	stats.velMov = 1000;
	stats.vida = 4;
}


Tostadora::~Tostadora()
{

	delete shape;
	shape = nullptr;
}

void Tostadora::onColisionEnter(Objeto* contactObject) {

	std::cout << "colision";
	stats.vida--;

}
Uint32 timerDisparo(Uint32 intervalo, void* param) {
	static_cast<Tostadora*>(param)->reactivarDisparo();
	return 0;
}
void Tostadora::disparo(){
	SDL_Rect posicion;
	int spawnPosition = 50;
	posicion.x = pos.x + sprite->w / 2;
	posicion.y = pos.y + sprite->h / 2;
	posicion.w = 10;
	posicion.h = 10;
	if (disparar) {
		if (pJuego->inputQuery(SDL_SCANCODE_DOWN)) {
				disparar = false;
				posicion.y += spawnPosition;
				dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, 1, 0));
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_RIGHT)) {
			disparar = false;
			posicion.x += spawnPosition;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 1, 0, 0));
				//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 2
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_LEFT)) {

			disparar = false;
			posicion.x -= spawnPosition;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, -1, 0, 0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 4));
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_UP)) {
			disparar = false;
			posicion.y -= spawnPosition;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, -1, 0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 1));
		}
		if(!disparar)Disparar = SDL_AddTimer(cadencia, timerDisparo, this);
	}

}
void Tostadora::update(){
	disparo();
	Jugable::update();
}