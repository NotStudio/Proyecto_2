#include "Jugable.h"



Jugable::Jugable(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Personaje(punteroJuego, spritePar, objectId)
{


	//Capa de colision.
	fDef.filter.categoryBits = Juego::JUGADOR;
	fDef.filter.maskBits = Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::ITEM | Juego::ESCENARIO;
	body->CreateFixture(&fDef);
	






}


Jugable::~Jugable()
{
	delete shape;
	shape = nullptr;
}



void Jugable::movControl(){


	int lim = stats.velMov;
	int ac = 0.5 * lim;

	b2Vec2 v = body->GetLinearVelocity();


	if (pJuego->inputQuery(SDL_SCANCODE_A)) {
		Dir.izq = true;
		if (!(v.x < -lim))
			vel.x -= ac;
	}
	else
		Dir.izq = false;

	if (pJuego->inputQuery(SDL_SCANCODE_D)) {
		if (!(v.x > lim)) {
			vel.x += ac;
		}
		Dir.der = true;

	}
	else
		Dir.der = false;

	if (pJuego->inputQuery(SDL_SCANCODE_W)) {
		if (!(v.y < -lim))
			vel.y -= ac;
		Dir.arr= true;

	}
	else
		Dir.arr = false;

	if (pJuego->inputQuery(SDL_SCANCODE_S)) {
		if (!(v.y > lim))
			vel.y += ac;
		Dir.aba = true;

	}
	else
		Dir.aba = false;
	//Para que frene solo y para controlar que no se salga.
	if (!lel) {
		if (Dir.aba || Dir.arr || Dir.izq || Dir.der) {
			currentAnim = animaciones[1];
		}
		else
			currentAnim = animaciones[0];
	}
		afinarMov(ac, lim);
}

void Jugable::afinarMov(int ac, int lim) {

	//Para que pare solo.
	if (!Dir.der && !Dir.izq) {
		if (vel.x != 0) {
			if (vel.x > 0)
				vel.x -= ac;
			else
				vel.x += ac;
		}
	}
	if (!Dir.arr && !Dir.aba) {
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
	body->SetLinearVelocity(velFloat);
}

void Jugable::update() {
	move();
	Personaje::update();

}