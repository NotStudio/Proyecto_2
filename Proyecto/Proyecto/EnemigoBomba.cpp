#include "EnemigoBomba.h"
#include <math.h>
#include "Jugable.h"
#include "Bala.h"
#include "BalaAmiga.h"
EnemigoBomba::EnemigoBomba(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, {x,y,128,128}, "Bomba", 400)
{
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	isKillable = true;
	currentAnim = animaciones.at("walk");
	stats.daño = 20;
	stats.velAtq = 0;
	stats.velMov = 0.7;
	stats.vida = 40;
	visible = true;
	
}


EnemigoBomba::~EnemigoBomba()
{
}


void EnemigoBomba::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (contactObject != nullptr){
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR){
			muerte();
		}
		else if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {
			stats.vida -= static_cast<BalaAmiga*>(contactObject)->getDanyo();
			(stats.vida <= 0) ? muerte() : nullptr;
		}
	}
}


void EnemigoBomba::move(){
	if (distancia()){
		jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
		jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();

		b2Vec2 velFloat;
		velFloat.x = 0.0f;
		velFloat.y = 0.0f;

		b2Vec2 posJug = b2Vec2(jugx / PPM, jugy / PPM);

		b2Vec2 vecDir = posJug - pos;

		b2Vec2 vUnitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

		velFloat.x = vUnitario.x*stats.velMov;
		velFloat.y = vUnitario.y*stats.velMov;
		if (velFloat.x > 0) {
			estadoEntidad.mirando = Oeste;
		}else if (velFloat.x < 0)
			estadoEntidad.mirando = Este;
		body->SetLinearVelocity(velFloat);
		currentAnim->ActualizarFrame();
	}
	else {
		stop();
	}

}

void EnemigoBomba::crecer(){

	int i = abs(jugx - pos.x * PPM);
	int j = abs(jugy - pos.y* PPM);

	
	if ((i < 250 || j < 250) && sprite->h <= 70){
		sprite->h++;
		sprite->w++;
		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		stats.velMov = 1.2;
	}
	if ((i < 175 || j < 175) && sprite->h <= 90){
		sprite->h++;
		sprite->w++;
		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		stats.velMov = 2.1;
	}
	if ((i < 100 || j < 100) && sprite->h <= 120){
		sprite->h++;
		sprite->w++;

		body->DestroyFixture(body->GetFixtureList());
		delete shape;
		shape = new b2PolygonShape;
		static_cast<b2PolygonShape*>(shape)->SetAsBox((sprite->w / PPM) / 2, (sprite->h / PPM) / 2, { (float)(sprite->w / PPM) / 2, (float)(sprite->h / PPM) / 2 }, 0);
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		body->CreateFixture(&fDef);
		stats.velMov = 3.5;
	}

	if ((i > 150 || j > 150) && sprite->h > 50){
		sprite->h--;
		sprite->w--;
	}
}


void EnemigoBomba::muerte(){
	pJuego->reproducirEfecto("Boom");
	Enemigo::muerte();
}


void EnemigoBomba::comportamiento(){
	move();
	crecer();
}

