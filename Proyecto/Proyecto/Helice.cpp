#include "Helice.h"
#include "ZonaAccion.h"
#include "BalaEnemiga.h"
#include "BalaAmiga.h"


Helice::Helice(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, {x,y,60,64}, "OV", 475)
{
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idle");
	stats.daño = 10;
	stats.velAtq = 1.4;
	cadencia = stats.velAtq * 1000;
	stats.velMov = 2;
	stats.vida = 20;
	isKillable = true;
	rng = rand() % 2;
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::AT_JUGADOR;
	fDef.shape = shape; fDef.density = 25.0f; fDef.friction = 1.0f;
	body->CreateFixture(&fDef);
	
}
void Helice::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	

	if (contactObject != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {
			stats.vida -= static_cast<BalaAmiga*>(contactObject)->getDanyo();
			if (stats.vida <= 0)
				muerte();
		}
	}
}


Helice::~Helice()
{
}


void Helice::move(){

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

	body->SetLinearVelocity(velFloat);

}

void Helice::disparo(){

	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;

	b2Vec2 posJug = b2Vec2(x / PPM, y / PPM);
	//Vector para la diferencia entre el vect del jugador y el vect del enemigoPerseguidor
	b2Vec2 vecDir = posJug - pos;

	//Calculamos el vector unitario del vector de direccion.
	b2Vec2 unitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

	velFloat.x = unitario.x;
	velFloat.y = unitario.y;
	SDL_Rect posicion;
	posicion.x = pos.x * PPM + sprite->w / 2;
	posicion.y = pos.y * PPM + sprite->h / 5;
	posicion.w = 30;
	posicion.h = 30;

	posicion.x += velFloat.x * 70;
	posicion.y += velFloat.y * 70;
	Uint32 lastUpdate = SDL_GetTicks();
	//	cout << contador;
	if (lastUpdate - contador > cadencia) {
		//contador++;
		contador = SDL_GetTicks();
		//cout << " Velx " << velFloat.x << " Vely  " << velFloat.y;
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, "BallTBala", 15.0f, velFloat.x, velFloat.y, stats.daño));
	}

}

void Helice::comportamiento(){
	currentAnim->ActualizarFrame();
	if (distancia()){

		if (rng == 0){
			disparo();
			stop();
		}
		else
			move();
	}
	else
		rng = rand() % 2;
}