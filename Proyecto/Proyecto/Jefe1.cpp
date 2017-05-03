#include "Jefe1.h"
#include "BalaAceite.h"

#include "BalaEnemiga.h"
#include "BalaAmiga.h"

Jefe1::Jefe1(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x, y, 128, 128}, "Bomba", 1000)// pone bomba pero está claro que no
{
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	estado = Estados::Idle;
	fase = Fases::Fase1;
	contador = 0;// Contador de la en que parte d ela fase te encuentras
	stats.vida = 30;
	for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("walk");
	body->SetType(b2_staticBody);
}


Jefe1::~Jefe1()
{
}


void Jefe1::comportamiento(){

	if (!destruido){
		switch (estado)
		{
		case Estados::Idle:
			Idle();
			break;
		case Estados::Ataque1:
			Ataque1();
			break;
		case Estados::Ataque2:
			Ataque2();
			break;
		case Estados::Ataque3:
			Ataque3();
			break;
		case Estados::Ataque4:
			Ataque4();
			break;
		}
	}


}

void Jefe1::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {
	if (contactObject != nullptr){
		cout << "colision" << endl;
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR){

			stats.vida--;
			//pJuego->reproducirEfecto("scream");
			cout << "El jefe tiene " << stats.vida << endl;
			if (stats.vida == 15)fase = Fases::Fase2;
			else  if (stats.vida <= 0) muerte();
		}
	}
}


void Jefe1::move(){
	currentAnim->ActualizarFrame();
}
uint32 changeStateCb(Uint32 intervalo, void * param){
	static_cast<Jefe1*>(param)->changeState();
	return 0;
}

void Jefe1::changeState(){// El metodo no es el más bonito lo sé
	empezado = false;
	if (estado == Estados::Idle ){
		
		int rdm = rand() % 2;
		if(rdm == 0)estado = Estados::Ataque1;
		if (rdm == 1)
		{
			if(fase == Fases::Fase1)
			estado = Estados::Ataque2;
			else if (fase == Fases::Fase2)
				estado = Estados::Ataque3;
		}
	
	}
	else estado = Estados::Idle;
}

void Jefe1::Idle(){
	if (!empezado){
		empezado = true;
		Uint32 random = (rand() % 2000) + 1000;
	
		SDL_AddTimer(random, changeStateCb, this);
		//timers
		//El timer que se activa mas tarde es el changestate
	}
}

void Jefe1::Ataque1(){
	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(500u, changeStateCb, this);
	
		
		//disparaAceite();
		
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, -0.8, 0.3, 10);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 0, 1, 10);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 0.7, 0.8, 10);
		disparo("BalaN", SDL_Rect{ getX(), getY() + 150, 24, 24 }, 1.5, 0.4, 10);
		


	}
	//timers
	//El timer que se activa mas tarde es el changestate
}


void Jefe1::Ataque2(){
	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(300u, changeStateCb, this);
		float randomx = (rand() % 200) + -100; randomx /= 100;
		float randomy = (rand() % 100); randomy /= 100;
		cout << randomx << " " << randomy << endl;

		disparo("BalaN", SDL_Rect{ getX(), getY() + 200, 60, 60 }, randomx, randomy, 20);
		//disparaAceite(randomx,randomy);

	}
}

void Jefe1::Ataque3(){
	if (!empezado){
		empezado = true;
		contador = 0;
		tiempo.start();
		SDL_AddTimer(300u, changeStateCb, this);
		float randomx = (rand() % 200) + -100; randomx /= 100;
		float randomy = (rand() % 100); randomy /= 100;
		cout << randomx << " " << randomy << endl;

		//disparo("Bala", SDL_Rect{ getX(), getY() + 200, 24, 24 }, randomx, randomy, 10);
		disparaAceite(randomx, randomy);
	}
}

void Jefe1::Ataque4(){
	if (!empezado){
		empezado = true;

		//timers
		//El timer que se activa mas tarde es el changestate
	}
}

void Jefe1::disparo(string tipo,SDL_Rect posicion, float dirx, float diry,float velocidad){
	//dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, tipo, velocidad, dirx, diry));
	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaEnemiga(pJuego, posicion, tipo, velocidad, dirx, diry));
}
void Jefe1::disparaAceite(float dirx,float diry){
	b2Vec2 objetivo;
	
	SDL_Rect kek{ pos.x * PPM, pos.y * PPM + 200, 24, 24 };

	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaAceite(pJuego, kek, dirx*20.0f, diry*20.0f));
}


