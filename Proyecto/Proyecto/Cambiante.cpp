#include "Cambiante.h"
#include "Bala.h"
#include "Play.h"
#include "checkML.h"
#include "Room.h"
#include "ZonaAccion.h"


Cambiante::Cambiante(Juego* punteroJuego, SDL_Rect spritePar) :Jugable(punteroJuego, spritePar, "Tostadora")
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

	/*bdt.type = b2_dynamicBody;
	bdt.position.Set(pos.x, pos.y);
	bdt.fixedRotation = true;
	bt = pJuego->getWorld()->CreateBody(&bdt);

	bt->SetUserData(this);
	st = new b2PolygonShape;
	static_cast<b2PolygonShape*>(st)->SetAsBox(64, 64, { (float)(sprite->w / 2), (float)(sprite->h / 2) }, 0);
	fdt.shape = st; fdt.density = 5.0f; fdt.friction = 0;

	fdt.filter.categoryBits = Juego::AT_JUGADOR;
	fdt.filter.maskBits = Juego::ENEMIGO;
	bt->CreateFixture(&fdt);*/
}


Cambiante::~Cambiante()
{
}


Uint32 imerDisparo(Uint32 intervalo, void* param) {
	static_cast<Cambiante*>(param)->reactivarDisparo();
	return 0;
}

Uint32 melee(Uint32 intervalo, void* param) {
	static_cast<Cambiante*>(param)->reactivarMele();
	return 0;
}


/****************FORMAS DE ATAQUE*****************/

void Cambiante::disparo(){
	Direccion aux = SinDir;
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
			aux = Norte;
			disparar = false;
			posicion.y -= spawnPosition;
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new Bala(pJuego, posicion, sprite, 80.0f, 0, -1, 0));
		}
		if (!disparar) {
			Disparar = SDL_AddTimer(cadencia, imerDisparo, this); pJuego->reproducirEfecto("TShot");
			currentAnim = animaciones.at("atqu");
		furia += 5;// incrementa furia...............................
		}
	}
	if (aux != SinDir) {
		estadoEntidad.mirando = aux;
	}
	else if (!disparar)
	{
		estadoEntidad.animacionActual = NoAnim;
	}
}


void Cambiante::ataqueMele(){
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
		atamele = SDL_AddTimer(1000000, melee, this); pJuego->reproducirEfecto("TShot");
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
			static_cast<b2PolygonShape*>(st)->SetAsBox(64, 64, { (float)(sprite->w / 2), (float)(sprite->h / 2) + 32 }, 0);
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
			static_cast<b2PolygonShape*>(st)->SetAsBox(64, 64, { (float)(sprite->w / 2) + 32, (float)(sprite->h / 2) }, 0);
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
			static_cast<b2PolygonShape*>(st)->SetAsBox(64, 64, { (float)(sprite->w / 2) - 32, (float)(sprite->h / 2) }, 0);
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
			static_cast<b2PolygonShape*>(st)->SetAsBox(64, 64, { (float)(sprite->w / 2), (float)(sprite->h / 2) - 32 }, 0);
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
	else if (!disparar)
	{
		estadoEntidad.animacionActual = NoAnim;
	}
}


void Cambiante::forma(bool mele){// Falta cambiar sprites...

	int aux = 7;//vidamax en grande

	if (!mele){//diminuye
		////////////////////////////////stats
		stats.velMov += 400;
		stats.vida -= 3;
		stats.daño -= 2;
		stats.velAtq = 3;
		stats.vidaMax = stats.vida;
	
		/////////////////////////////////////////tamaño sprite y colision,  , , , ,, falta cambiar sprite
		while (sprite->h >= 65){
			sprite->h--;
			sprite->w--;
		}

		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
/////////////////////////////////////
	}

	if (mele){//aumenta

		stats.velMov -= 400;/* Decidir más tarde las características*/
		stats.vida += 3;
		stats.daño += 2;
		stats.velAtq = 3;
		stats.vidaMax = stats.vida;

		while (sprite->h < 96){
			sprite->h++;
			sprite->w++;
		}

		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
	}

}


/////////////////////////////////////////////////////////////////////////


void Cambiante::cambio(){

	if (furia >= 100){
		furia = 100;
		mele = !mele;
		forma(mele);
	}
	else if (furia <= 0){
		furia = 1;
		mele = !mele;
		forma(mele);
	}
}



void Cambiante::update(){
	move();
	cambio();// Cambia de forma según el valor de la furia.
	std::cout << furia;
	if (state == JUGANDO){
		if (!mele)
			disparo();
		else{
			ataqueMele();
			furia-= 0.2f;
		}
	}

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
