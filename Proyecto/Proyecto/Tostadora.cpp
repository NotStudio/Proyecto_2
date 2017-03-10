#include "Tostadora.h"
#include "Bala.h"
#include "Play.h"



Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	//Física
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x, pos.y);
	body = pJuego->getWorld()->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2Vec2 Puntos[4];
	Puntos[0] = b2Vec2(0, 32);
	Puntos[1] = b2Vec2(0, 64);
	Puntos[2] = b2Vec2(64, 64);
	Puntos[3] = b2Vec2(64, 32);
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->Set(Puntos, 4);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	//Capa de colision.
	fDef.filter.categoryBits = Juego::JUGADOR;
	fDef.filter.maskBits = Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::ITEM | Juego::ESCENARIO;
	body->CreateFixture(&fDef);
	stats.velMov = 1750;

	stats.vida = 4;
}


Tostadora::~Tostadora()
{
	delete shape;
}

void Tostadora::onColisionEnter(Objeto* contactObject) {

	std::cout << "colision";
	stats.vida--;

}

void Tostadora::disparo(){
	SDL_Rect posicion;

	posicion.x = pos.x + sprite->w / 2;
	posicion.y = pos.y + sprite->h / 2;
	posicion.w = 10;
	posicion.h = 10;
	Uint32 lastUpdate = SDL_GetTicks();

	if (pJuego->inputQuery(SDL_SCANCODE_DOWN)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.y += 75;

			EstadoJuego*estado;

			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, 1));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_RIGHT)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.x += 75;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 1, 0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 2));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_LEFT)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.x -= 75;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, -1, 0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 4));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_UP)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.y -= 75;

			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, -1));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 1));
		}
	}

}
void Tostadora::update(){
	disparo();
	Jugable::update();
}