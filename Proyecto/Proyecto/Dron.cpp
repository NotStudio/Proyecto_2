#include "Dron.h"
#include "BalaEnemiga.h"



Dron::Dron(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x,y,128,128 }, "OV", 200), doDieAction(false)
{
	//a ver si funciona
	delete shape;
	shape = new b2CircleShape;
	static_cast<b2CircleShape*>(shape)->m_p.Set(sprite->w / 2, sprite->h / 2);
	static_cast<b2CircleShape*>(shape)->m_radius = sprite->h / 2;
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;


	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	//currentAnim = animaciones.at("walk");
	stats.daño = 100;
	stats.velAtq = 20;
	stats.velMov = 10;
	stats.vida = 3; stats.vidaMax = stats.vida;
	//Inicializamos la dirección aleatoriamente.
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
}


Dron::~Dron()
{
}

void Dron::move() {
	body->SetLinearVelocity(vel);
}
void Dron::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (b2 != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {
			//hit(static_cast<Jugable*>(contactObject)->getStats()->daño);
			muerte();
		}
		else if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO) {
			rebote(b2);
		}
	}
};

void Dron::hit(int dmg) {

	int lim1, lim2;
	lim1 = 0.6 * stats.vidaMax;
	lim2 = 0.3 * stats.vidaMax;

	stats.vida -= dmg;
	//Si se queda sin vida, lo eliminamos.
	if (stats.vida <= 0) {
		muerte();
	}
	else {
		if (stats.vida > lim1 && stats.vida < stats.vidaMax) {
			//Animación 1
		}
		else if (stats.vida > lim2 && stats.vida < lim1) {
			//Animacion 2
		}
		else if (stats.vida > 0 && stats.vida < lim2) {
			//Animacion 3
		}
	}
}

void Dron::muerte() {
	Enemigo::muerte();
};
void Dron::comportamiento() {

	move();

};

void Dron::desactivar() {
	Enemigo::desactivar();
	spawnBalas();
}

void Dron::spawnBalas() {
	b2Vec2 origPos = body->GetPosition();
	float radio = body->GetFixtureList()->GetShape()->m_radius - 20;
	SDL_Rect posicion{ 0,0,24,24 };
	float velocidad, dirx, diry, angle;
	velocidad = (float)stats.velAtq;
	//Spawn las 6 balas alrededor

	for (float i = 1.0f; i < 8.0f; i++) {
		angle = 360 / ((360.0f / 7.0f) * i);
		dirx = cos(6.28 / angle);  diry = sin(6.28 / angle);
		posicion.x = radio * cos(6.28 / angle) + origPos.x;  posicion.y = radio * sin(6.28 / angle) + origPos.y;
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, "BalaN", velocidad, dirx, diry));
	}
}

void Dron::rebote(b2Body* tileBody) {

	bool bounced = false;
	bool isCircle = false;
	b2Vec2 boxExtents;
	float radius = 0;
	float collisionDistance;

	if (tileBody->GetFixtureList()->GetShape()->m_type = b2Shape::e_circle) {
		radius = static_cast<b2CircleShape*>(tileBody->GetFixtureList()->GetShape())->m_radius;
		isCircle = true;
	}
	else if (tileBody->GetFixtureList()->GetShape()->m_type = b2Shape::e_polygon)
		boxExtents = static_cast<b2PolygonShape*>(tileBody->GetFixtureList()->GetShape())->GetVertex(1);



	//Hacemos calculos diferentes dependiendo si el shape colisionado es un circulo o un cuadrado.
	if (isCircle)
		collisionDistance = radius + body->GetFixtureList()->GetShape()->m_radius;
	else
		collisionDistance = boxExtents.y / 2 + body->GetFixtureList()->GetShape()->m_radius;

	//Hacemos los calculos de rebote
	float myYPos = body->GetPosition().y;
	float tileYPos = tileBody->GetPosition().y;
	float myXPos = body->GetPosition().x;
	float tileXPos = tileBody->GetPosition().x;

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
}
