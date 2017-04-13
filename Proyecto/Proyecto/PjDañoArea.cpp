#include "PjDañoArea.h"


PjDañoArea::PjDañoArea(Juego* punteroJuego, SDL_Rect spritePar) :Jugable(punteroJuego, spritePar, "Tostadora")
{

	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones.at(i->first)->setNumFrames(30);
	}
	currentAnim = animaciones.at("idle");
	//Inicializacion de los stats y stats máximos;
	stats.velMov = 1000;/* Decidir más tarde las características*/
	stats.vida = 4;
	stats.daño = 1;
	stats.velAtq = 3;
	stats.vidaMax = stats.vida;
}


PjDañoArea::~PjDañoArea()
{
}

Uint32 melee2(Uint32 intervalo, void* param) {
	static_cast<PjDañoArea*>(param)->reactivarMele();
	return 0;
}


void PjDañoArea::ataqueMele(){//////////// Ataca en área alrededor del personaje, cualquiera de las flechas sirve igual  ///////////////////////
	Direccion aux = SinDir;
	SDL_Rect posicion;
	int spawnPosition = 50;
	posicion.x = sprite->x + sprite->w / 2 - 15;
	posicion.y = sprite->y + sprite->h / 2 - 15;
	posicion.w = 30;
	posicion.h = 30;

	if (destroyBody){
		if (bt != nullptr){
			b2Fixture* y;
			y = bt->GetFixtureList();
			bt->DestroyFixture(y);
			pJuego->getWorld()->DestroyBody(bt);
			destroyBody = false;
		}
	}

	if (!atamele) {
		atamele = SDL_AddTimer(1000000, melee2, this); pJuego->reproducirEfecto("TShot");
		currentAnim = animaciones.at("atqu");
	}

	if (atamele){

		if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

			bdt.type = b2_dynamicBody;
			bdt.position.Set(pos.x, pos.y);
			bdt.fixedRotation = true;
			bt = pJuego->getWorld()->CreateBody(&bdt);

			bt->SetUserData(this);
			st = new b2PolygonShape;
			static_cast<b2PolygonShape*>(st)->SetAsBox(96, 96, { (float)(sprite->w / 2), (float)(sprite->h / 2)}, 0);
			fdt.shape = st; fdt.density = 5.0f; fdt.friction = 0;

			fdt.filter.categoryBits = Juego::AT_JUGADOR;
			fdt.filter.maskBits = Juego::ENEMIGO;
			bt->CreateFixture(&fdt);


			atamele = false;
			destroyBody = true;
		}

		else if (pJuego->teclaPulsada(SDL_SCANCODE_RIGHT)) {

			bdt.type = b2_dynamicBody;
			bdt.position.Set(pos.x, pos.y);
			bdt.fixedRotation = true;
			bt = pJuego->getWorld()->CreateBody(&bdt);

			bt->SetUserData(this);
			st = new b2PolygonShape;
			static_cast<b2PolygonShape*>(st)->SetAsBox(96, 96, { (float)(sprite->w / 2), (float)(sprite->h / 2) }, 0);
			fdt.shape = st; fdt.density = 5.0f; fdt.friction = 0;

			fdt.filter.categoryBits = Juego::AT_JUGADOR;
			fdt.filter.maskBits = Juego::ENEMIGO;
			bt->CreateFixture(&fdt);


			atamele = false;
			destroyBody = true;

		}

		else if (pJuego->teclaPulsada(SDL_SCANCODE_LEFT)) {

			bdt.type = b2_dynamicBody;
			bdt.position.Set(pos.x, pos.y);
			bdt.fixedRotation = true;
			bt = pJuego->getWorld()->CreateBody(&bdt);

			bt->SetUserData(this);
			st = new b2PolygonShape;
			static_cast<b2PolygonShape*>(st)->SetAsBox(96, 96, { (float)(sprite->w / 2), (float)(sprite->h / 2) }, 0);
			fdt.shape = st; fdt.density = 5.0f; fdt.friction = 0;

			fdt.filter.categoryBits = Juego::AT_JUGADOR;
			fdt.filter.maskBits = Juego::ENEMIGO;
			bt->CreateFixture(&fdt);


			atamele = false;
			destroyBody = true;

		}

		else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {

			bdt.type = b2_dynamicBody;
			bdt.position.Set(pos.x, pos.y);
			bdt.fixedRotation = true;
			bt = pJuego->getWorld()->CreateBody(&bdt);

			bt->SetUserData(this);
			st = new b2PolygonShape;
			static_cast<b2PolygonShape*>(st)->SetAsBox(96, 96, { (float)(sprite->w / 2), (float)(sprite->h / 2)}, 0);
			fdt.shape = st; fdt.density = 5.0f; fdt.friction = 0;

			fdt.filter.categoryBits = Juego::AT_JUGADOR;
			fdt.filter.maskBits = Juego::ENEMIGO;
			bt->CreateFixture(&fdt);


			atamele = false;
			destroyBody = true;

		}


	}


	if (aux != SinDir) {
		estadoEntidad.mirando = aux;
	}
	else if (!atamele)
	{
		estadoEntidad.animacionActual = NoAnim;
	}
}

void PjDañoArea::update(){
	move();
	if (state == JUGANDO)
		ataqueMele();
	Entidad::update();
	if (!atamele) {
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