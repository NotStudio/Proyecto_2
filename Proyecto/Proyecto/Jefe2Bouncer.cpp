#include "Jefe2Bouncer.h"
#include "BalaEnemiga.h"
#include "ObjetoClave.h"
#include "ObjetoHistorico.h"


Jefe2Bouncer::Jefe2Bouncer(Juego* punteroJuego, int x, int y, int lvl):Enemigo(punteroJuego, { x, y, 300-(lvl*40), 300-(lvl*40) }, "PlasmaBall", 1000), level(lvl), doDivision(false)
{
	delete shape;
	shape = new b2CircleShape;
	static_cast<b2CircleShape*>(shape)->m_p.Set((sprite->w / PPM) / 2, (sprite->h / PPM) / 2);
	static_cast<b2CircleShape*>(shape)->m_radius = (sprite->h / PPM) / 2;
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);
	int velPlus = 3 / lvl;
	int vidaPlus = 50 / lvl;
	stats.vida = vidaPlus;
	stats.daño = 10;
	switch (lvl)
	{
	case 1: stats.velMov = 1; break;
	case 2: stats.velMov = 1.5; break;
	case 3: stats.velMov = 2.3; break;
	case 4: stats.velMov = 2.9; break;
	default: stats.velMov = 3; break;
		break;
	}
	tarjetaSpawned = false;
	isKillable = true;
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("atqu");

	int randAux1 = rand() % 2; int randAux2 = rand() % 2;

	if (randAux1 == 1) {
		dirX = 1;
	}
	else dirX = -1;
	if (randAux2 == 1) {
		dirY = 1;
	}
	else dirY = -1;

	vel.Set(stats.velMov * dirX, stats.velMov * dirY);
	move();
}


Jefe2Bouncer::~Jefe2Bouncer()
{
}

void Jefe2Bouncer::bounce(b2Body* tileBody)
{
	bool bounced = false;
	bool isCircle = false;
	b2Vec2 boxExtents;
	float radius = 0;
	float collisionDistance;

	if (tileBody->GetFixtureList()->GetShape()->m_type == b2Shape::e_circle) {
		radius = static_cast<b2CircleShape*>(tileBody->GetFixtureList()->GetShape())->m_radius * PPM;
		isCircle = true;
	}
	else if (tileBody->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon)
		boxExtents = static_cast<b2PolygonShape*>(tileBody->GetFixtureList()->GetShape())->GetVertex(1);



	//Hacemos calculos diferentes dependiendo si el shape colisionado es un circulo o un cuadrado.
	if (isCircle)
		collisionDistance = radius + body->GetFixtureList()->GetShape()->m_radius * PPM;
	else
		collisionDistance = boxExtents.y / 2 + body->GetFixtureList()->GetShape()->m_radius * PPM;

	//Hacemos los calculos de rebote
	float myYPos = body->GetPosition().y * PPM;
	float tileYPos = tileBody->GetPosition().y * PPM;
	float myXPos = body->GetPosition().x * PPM;
	float tileXPos = tileBody->GetPosition().x * PPM;

	if (myYPos > tileYPos) {//Comprobamos si se ha rebotado por arriba
		if (myYPos + collisionDistance >= tileYPos) {//Si que ha habido colisión.
			dirY = 1;
			bounced = true;
		}
	}
	else if (myYPos < tileYPos) {//Se ha colisionado por debajo
		if (myYPos + collisionDistance <= tileYPos) {
			dirY = -1;
			bounced = true;
		}
	}
	if (!bounced) {
		if (myXPos < tileXPos) {//Collisionado por la derecha
			dirX = -1;

		}
		else {//Colisionado por la izquierda
			dirX = 1;
		}

	}

	vel.Set(stats.velMov * dirX, stats.velMov *  dirY);
	move();
}

void Jefe2Bouncer::comportamiento() {
	currentAnim->ActualizarFrame();
	move();
}

void Jefe2Bouncer::onColisionEnter(Objeto * contactObject, b2Body * b1, b2Body * b2)
{
	if (b2 != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {
			stats.vida -= static_cast<BalaEnemiga*>(contactObject)->getDanyo();		
			if (stats.vida <= 0){
				doDivision = true;
				muerte();
			}
		}
		else if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO) {
			bounce(b2);
		}
	}
}

void Jefe2Bouncer::dropItems()
{
	if (level == 1){

		if (pJuego->getNumTarjetas() < 4)
			dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new ObjetoClave(pJuego, { sprite->x, sprite->y, 64, 64 }));

		int x; int y;
		int pos = rand() % 2;
		if (pos == 0) pos = -1;
		x = rand() % 10 * pos;
		y = rand() % 10 * (pos * -1);
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoObjeto(new ObjetoHistorico(pJuego, { sprite->x + x,sprite->y + y,64,64 }, "Eje", 1));
	}
	
}

void Jefe2Bouncer::move() {
	body->SetLinearVelocity(vel);
}


void Jefe2Bouncer::muerte() {
	Enemigo::muerte();
}

void Jefe2Bouncer::desactivar()
{
	Enemigo::desactivar();
	spawnSons();

}

void Jefe2Bouncer::spawnSons() {
	if (level < 5) {
		//Calculamo new pos
		int dirX = dirY = 0;
		if (rand() % 2 == 1) dirX = 1; else dirX = -1;
		if (rand() % 2 == 1) dirY = 1; else dirY = -1;
		
		int newX = body->GetPosition().x *PPM + dirX * (rand() % 10 + 10);
		int newY = body->GetPosition().y *PPM + dirY * (rand() % 10 + 10);
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoEnemigo(new Jefe2Bouncer(pJuego, newX, newY, level + 1));


		if (rand() % 2 == 1) dirX = 1; else dirX = -1;
		if (rand() % 2 == 1) dirY = 1; else dirY = -1;

		newX = body->GetPosition().x*PPM + dirX * (rand() % 10 + 10);
		newY = body->GetPosition().y*PPM + dirY * (rand() % 10 + 10);
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevoEnemigo(new Jefe2Bouncer(pJuego, newX, newY, level + 1));
	}
}