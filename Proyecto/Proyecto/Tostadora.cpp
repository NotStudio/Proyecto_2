#include "Tostadora.h"
#include "Bala.h"
#include "Play.h"
#include "checkML.h"
#include "Room.h"
#include "ZonaAccion.h"
class Room;
Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	currentAnim.setNumFrames(30);
	animaciones.push_back(currentAnim);
	Juego::Animacion a;
	a.loadTextura(pJuego->getTextura(id, "walk"),30);
	animaciones.push_back(a);
	a.loadTextura(pJuego->getTextura(id, "atqu"), 30);
	animaciones.push_back(a);
	stats.velMov = 1000;
	stats.vida = 4;
}


Tostadora::~Tostadora()
{
	delete shape;
	shape = nullptr;
}

void Tostadora::onColisionEnter(Objeto* contactObject) {
	currentAnim.ActualizarFrame();
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
			//pJuego->extras.push_back(new Bala(pJuego, posicion, "Bala", 50.0f, 1
		}
		if(!disparar)Disparar = SDL_AddTimer(cadencia, timerDisparo, this);
	}
	if (!disparar)currentAnim = animaciones[2];
	lel = !disparar;
}
void Tostadora::update(){
	disparo();
	currentAnim.ActualizarFrame();
	Jugable::update();
}