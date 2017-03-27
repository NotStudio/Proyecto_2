#include "Tostadora.h"
#include "Bala.h"
#include "Play.h"
#include "checkML.h"
#include "Room.h"
#include "ZonaAccion.h"
Tostadora::Tostadora(Juego* punteroJuego, SDL_Rect spritePar):Jugable(punteroJuego, spritePar, "Tostadora")
{	
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones.at(i->first)->setNumFrames(30);
	}
	currentAnim = animaciones.at("idle");
	//Inicializacion de los stats y stats máximos;
	stats.velMov = 1000;    
	stats.vida = 4;			
	stats.daño = 1;			
	stats.velAtq = 3;		
	stats.vidaMax = stats.vida; 
}


Tostadora::~Tostadora()
{
	
}
Uint32 timerDisparo(Uint32 intervalo, void* param) {
	static_cast<Tostadora*>(param)->reactivarDisparo();
	return 0;
}
void Tostadora::disparo(){
	Direccion aux=SinDir;
	SDL_Rect posicion;
	int spawnPosition = 50;
	posicion.x = sprite->x + sprite->w / 2 - 15;
	posicion.y = sprite->y + sprite->h / 2 - 15;
	posicion.w = 30;
	posicion.h = 30;
	std::string sprite = "DisparoToasty";
	if (disparar) {
		if (pJuego->inputQuery(SDL_SCANCODE_DOWN)) {
			aux = Sur;
				disparar = false;
				posicion.y += spawnPosition;
				dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, sprite, 80.0f, 0, 1, 0));
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_RIGHT)) {
			aux = Este;
			disparar = false;
			posicion.x += spawnPosition;
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, sprite, 80.0f, 1, 0, 0));
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_LEFT)) {
			aux = Oeste;
			disparar = false;
			posicion.x -= spawnPosition;
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, sprite, 80.0f, -1, 0, 0));
		
		}
		else if (pJuego->inputQuery(SDL_SCANCODE_UP)) {
			aux = Sur;
			disparar = false;
			posicion.y -= spawnPosition;
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, sprite, 80.0f, 0, -1, 0));
		}
		if (!disparar) {
			Disparar = SDL_AddTimer(cadencia, timerDisparo, this); pJuego->reproducirEfecto("scream");
			currentAnim = animaciones.at("atqu");
		}
	}
	if (aux != SinDir) {
		estadoEntidad.mirando = aux;
	}
	else if(!disparar)
	{
		estadoEntidad.animacionActual = NoAnim;
	}
}
void Tostadora::update(){
	move();
	disparo();
	Entidad::update();
	if (!disparar) {
		if (estadoEntidad.animacionActual != Ataque) {
			estadoEntidad.animacionActual = Ataque;
			currentAnim = animaciones.at("atqu");
		}
		currentAnim->ActualizarFrame();
	}
	else {
		if (estadoEntidad.animacionActual == Walk)
		{
			currentAnim = animaciones.at("walk");
		}
		else {
			currentAnim = animaciones.at("idle");
		}
		
	}
	currentAnim->ActualizarFrame();
}