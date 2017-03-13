#include "EnemigoBomba.h"
#include <math.h>

EnemigoBomba::EnemigoBomba(Juego* punteroJuego, SDL_Rect a) : Enemigo(punteroJuego, a, "Gato",300)
{

	enemyStats.daño = 100;
	enemyStats.velAtq = 0;
	enemyStats.velMov = 1;
	enemyStats.vida = 10;

	visible = true;

}


EnemigoBomba::~EnemigoBomba()
{
}


void EnemigoBomba::onColisionEnter(Objeto* contactObject) {
	muerte();
}


void EnemigoBomba::move(){
	if (distancia()){
		jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
		jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();

		b2Vec2 velFloat;
		velFloat.x = 0.0f;
		velFloat.y = 0.0f;

		b2Vec2 posJug = b2Vec2(jugx, jugy);

		b2Vec2 vecDir = posJug - pos;

		b2Vec2 vUnitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

		velFloat.x = vUnitario.x*enemyStats.velMov;
		velFloat.y = vUnitario.y*enemyStats.velMov;

		body->SetLinearVelocity(velFloat);
	}
	else {
		stop();
	}

}

void EnemigoBomba::crecer(){

	int i = abs(jugx - pos.x);
	int j = abs(jugy - pos.y);	

	
	if ((i < 250 || j < 250) && sprite->h <= 70){
		sprite->h++;
		sprite->w++;
		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		enemyStats.velMov = 2;
	}
	if ((i < 175 || j < 175) && sprite->h <= 90){
		sprite->h++;
		sprite->w++;
		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		enemyStats.velMov = 3;
	}
	if ((i < 100 || j < 100) && sprite->h <= 120){
		sprite->h++;
		sprite->w++;
		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		enemyStats.velMov = 6;
	}

	if ((i > 150 || j > 150) && sprite->h > 50){
		sprite->h--;
		sprite->w--;
	}

}


void EnemigoBomba::muerte(){
	visible = false;
}




void EnemigoBomba::update(){

	if (visible){
		Entidad::update();
		move();
		crecer();
	}

}


void EnemigoBomba::draw(){
	if (visible)
		Entidad::draw();
}