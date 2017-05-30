#include "BalaHacha.h"


BalaHacha::BalaHacha(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) : BalaEnemiga(pJuego, spritePar, "BalaN", 12, dirx, diry, 10)
{
	dirx_ = dirx;
	diry_ = diry;
}


BalaHacha::~BalaHacha()
{
}

void BalaHacha::update(){
	Bala::update();
}

void BalaHacha::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){

	if (numRebotes == rebotes){
		destruido = true;
	}

	else{
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR)
			destruido = true;

		else if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO 
					/*|| b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ESCENARIO_NOCOL*/){
		
			bounce(b2);

			numRebotes++;
		}
	}
}

void BalaHacha::bounce(b2Body* tileBody) {

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
			diry_ = 1;
			bounced = true;
		}
	}
	else if (myYPos < tileYPos) {//Se ha colisionado por debajo
		if (myYPos + collisionDistance <= tileYPos) {
			diry_ = -1;
			bounced = true;
		}
	}
	if (!bounced) {
		if (myXPos < tileXPos) {//Collisionado por la derecha
			dirx_ = -1;

		}
		else {//Colisionado por la izquierda
			dirx_ = 1;
		}

	}


	velocidad.Set(_vel * dirx_, _vel *  diry_);
	body->SetLinearVelocity(velocidad);

	

}