#include "Jugable.h"



Jugable::Jugable(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Personaje(punteroJuego, spritePar, objectId)
{
	dcha = izq = up = down = false;
}


Jugable::~Jugable()
{
}



void Jugable::movControl(){


	int lim = stats.velMov;
	int ac = lim / 15;

	b2Vec2 v = body->GetLinearVelocity();


	if (pJuego->inputQuery(SDL_SCANCODE_A)) {
		izq = true;
		if (!(v.x < -lim))
			vel.x -= ac;
	}
	else
		izq = false;

	if (pJuego->inputQuery(SDL_SCANCODE_D)) {
		if (!(v.x > lim)) {
			vel.x += ac;
		}
		dcha = true;

	}
	else
		dcha = false;

	if (pJuego->inputQuery(SDL_SCANCODE_W)) {
		if (!(v.y < -lim))
			vel.y -= ac;
		up = true;

	}
	else
		up = false;

	if (pJuego->inputQuery(SDL_SCANCODE_S)) {
		if (!(v.y > lim))
			vel.y += ac;
		down = true;

	}
	else
		down = false;

	//Para que frene solo y para controlar que no se salga.
	afinarMov(ac, lim);

}

void Jugable::afinarMov(int ac, int lim) {

	//Para que pare solo.
	if (!dcha && !izq) {
		if (vel.x != 0) {
			if (vel.x > 0)
				vel.x -= ac;
			else
				vel.x += ac;
		}
	}
	if (!up && !down) {
		if (vel.y != 0) {
			if (vel.y > 0)
				vel.y -= ac;
			else
				vel.y += ac;
		}
	}
	//Para que no se salga de los límites.
	if (vel.x >= lim || vel.x <= -lim) {
		if (vel.x > 0)
			vel.x = lim;
		else
			vel.x = -lim;
	}
	if (vel.y >= lim || vel.y <= -lim) {
		if (vel.y > 0)
			vel.y = lim;
		else
			vel.y = -lim;
	}



}

void Jugable::move() {
	movControl();
	//Movimiento;
	b2Vec2 velFloat;
	velFloat.x = (float32)vel.x / 40;
	velFloat.y = (float32)vel.y / 40;
	//std::cout << vel.x << "\n";
	//std::cout << " POS" << pos.x << "\n";
	body->SetLinearVelocity(velFloat);
}

void Jugable::update() {
	move();
	Personaje::update();

}