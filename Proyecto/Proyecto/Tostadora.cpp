#include "Tostadora.h"
#include "Bala.h"
#include "Play.h"
#include "checkML.h"

Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	stats.velMov = 1000;
	stats.vida = 4;
}


Tostadora::~Tostadora()
{
	
}

void Tostadora::onColisionEnter(Objeto* contactObject) {

	std::cout << "colision";
	stats.vida--;

}

void Tostadora::disparo(){
	SDL_Rect posicion;
	int spawnPosition = 50;
	posicion.x = pos.x + sprite->w / 2;
	posicion.y = pos.y + sprite->h / 2;
	posicion.w = 10;
	posicion.h = 10;
	Uint32 lastUpdate = SDL_GetTicks();

	if (pJuego->inputQuery(SDL_SCANCODE_DOWN)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.y += spawnPosition;

			EstadoJuego*estado;

			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, 1,0));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_RIGHT)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.x += spawnPosition;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 1, 0,0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 2));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_LEFT)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.x -= spawnPosition;
			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, -1, 0,0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 4));
		}
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_UP)){
		if (lastUpdate - contador > cadencia){
			contador = SDL_GetTicks();
			posicion.y -= spawnPosition;

			dynamic_cast<Play*>(pJuego->topState())->extras.push_back(new Bala(pJuego, posicion, "Bala", 80.0f, 0, -1,0));
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 1));
		}
	}

}
void Tostadora::update(){
	disparo();
	Jugable::update();
}