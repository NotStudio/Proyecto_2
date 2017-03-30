#include "Sierra.h"


Sierra::Sierra(Juego* punteroJuego, int x, int y, int dir) : Enemigo(punteroJuego, {x,y,128,81}, "Sierra", 1000)
{
	stats.daño = 1;
	stats.velAtq = 0;
	stats.velMov = 2;
	stats.vida = 1;
	direccion = dir;
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones[0];
	col = false;
	
	body->GetFixtureList()->SetSensor(true);
	b2Filter filter;
	filter = body->GetFixtureList()->GetFilterData();
	
	filter.categoryBits = Juego::ENEMIGO;
	filter.maskBits = Juego::ESCENARIO | Juego::JUGADOR |  Juego::ESCENARIO_NOCOL;
	
	body->GetFixtureList()->SetFilterData(filter);
	//HAY QUE PONER EN TILE
	/* //mShapeDef->filter.categoryBits = Juego::ESCENARIO;
		//mShapeDef->filter.maskBits = -1; 
	*/
	
}


Sierra::~Sierra()
{
}


void Sierra::move(){
	if (direccion == 0){

		b2Vec2 velFloat;
		velFloat.x = stats.velMov;
		velFloat.y = 0;
		if (col){
			stats.velMov = -stats.velMov;
			col = false;
		}
		body->SetLinearVelocity(velFloat);
	}

	else 
	{
		b2Vec2 velFloat;
		velFloat.x = 0;
		velFloat.y = stats.velMov;
		if (col){
			stats.velMov = -stats.velMov;
			col = false;
		}
		body->SetLinearVelocity(velFloat);
	}
}


void Sierra::update(){
	move();
	currentAnim->ActualizarFrame();
	Enemigo::update();
}

void Sierra::onColisionEnter(Objeto* contactObject) {

		col = true;

	
}