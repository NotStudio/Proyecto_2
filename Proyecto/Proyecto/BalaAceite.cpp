#include "BalaAceite.h"



BalaAceite::BalaAceite(Juego *pJuego, SDL_Rect spritePar, float dirx, float diry) :Bala(pJuego, spritePar, "BalaA", 1.0f, dirx, diry,1)
{
	tiempoCharco = 3000;
	distViajada = 0;
	distMax = 300;
	origen = b2Vec2(spritePar.x, spritePar.y);
	faseact = fase::viajando;
	

}


BalaAceite::~BalaAceite()
{
}

void BalaAceite::grow() {
	sprite->w *= 4;
	sprite->h *= 4;
	body->DestroyFixture(body->GetFixtureList());
	delete shape;
	shape = new b2PolygonShape;
	static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
	fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
	body->CreateFixture(&fDef);
	body->GetFixtureList()->SetSensor(true);
	//parate

}
void BalaAceite::changePhase() {
	body->SetLinearVelocity(b2Vec2(0, 0));
	faseact = fase::parada;
	contador = LTimer();
	contador.start();
	grow();
}

void BalaAceite::update(){
	Entidad::update();

	if (faseact == fase::viajando) {
		float aux1, aux2;
		aux1 = origen.x - pos.x;
		aux2 = origen.y - pos.y;
		distViajada = sqrt(pow(aux1, 2) + pow(aux2, 2));

		if (choque || distViajada > distMax) {
			float32 aux = distViajada;
			printf("La distansia fue %f \n", aux);
			changePhase();


		}
	}
	else {
		if (contador.getTicks() > tiempoCharco)
			destruido = true;

	}
}

void BalaAceite::onColisionEnter(Objeto* contactObject) {

	choque = true;
	
		
		/*
		Entidad* aux = dynamic_cast<Entidad *> (contactObject);
		b2Vec2 centro;
		centro.x = (pos.x + sprite->w) / 2;
		centro.y = (pos.y + sprite->h) / 2;

		if (aux->getX() > centro.x)
		{
			pos.x += (sprite->w) / 2 + 15;
		}
		else {
			pos.x -= (sprite->w) / 2 - 15;

		}
		if (aux->getY() > centro.y) {
			pos.y += (sprite->w) / 2 + 15;
		}
		else {
			pos.y -= (sprite->w) / 2 - 15;

		}*/
		

		

		//Pequeño problema al cambiar de fase, nos da nullptr
	
}

