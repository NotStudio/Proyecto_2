#include "Gnomo.h"


Gnomo::Gnomo(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x, y, 96, 96}, "gnomo", 1000)
{

	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	estado = IDLE;
	fase = FASE1;

	stats.daño = 10;
	stats.vida = 300;
	stats.velMov = 0;

	/*for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idlo");*/
	body->SetType(b2_staticBody);
}


Gnomo::~Gnomo()
{
}

void Gnomo::comportamiento() {

	currentAnim->ActualizarFrame();
	if (!destruido) {
		switch (estado)
		{
		case Estados::IDLE:
			Idle();
			break;
		case Estados::MOVIMIENTO:
			Movimiento();
			break;
		case Estados::ATAQUE1:
			Ataque1();
			break;
		case Estados::ATAQUE2:
			Ataque2();
			break;
		case Estados::ATAQUE3:
			Ataque3();
			break;
		
		}
	}
}

void Gnomo::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2) {

	if (contactObject != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {

			//stats.vida--; Hay que fixearlo...
			
			if (stats.vida == 15) fase = FASE2;// Sería la mitad de la vida...
			else  if (stats.vida <= 0) muerte();
		}
	}
}

void Gnomo::eliminaSierra() {

	dynamic_cast<Enemigo*>(sierras[sierras.size() - 1])->muerte();
	sierras.pop_back();
}


uint32 changeStateCB(Uint32 intervalo, void * param){
	static_cast<Gnomo*>(param)->changeState();
	return 0;
}

uint32 quitarSierraCB(Uint32 intervalo, void * param) {
	static_cast<Gnomo*>(param)->eliminaSierra();
	return 0;
}

void Gnomo::changeState(){

	empezado = false;
	Estados viejo = estado;
	if (estado == Estados::IDLE) {

		int rdm = rand() % 2;
		if (rdm == 0) estado = ATAQUE1;
		if (rdm == 1)
		{
			if (fase == FASE1)
				estado = ATAQUE2;
			else if (fase == FASE2) {
				rdm = rand() % 2;
				if (rdm == 0) estado = ATAQUE2;
				if (rdm == 1) estado = ATAQUE3;
			}
		}

	}
	else estado = IDLE;
	if (estado != viejo) {
		currentAnim->restart();
		switch (estado)
		{
		case IDLE:
			currentAnim = animaciones.at("idlo");
			break;
		case  ATAQUE1:
			currentAnim = animaciones.at("atqu");//....
			break;
		case  ATAQUE2:
			currentAnim = animaciones.at("aceite");//.....
			break;
		case  ATAQUE3:
			currentAnim = animaciones.at("aceite");//....
			break;
		case  MOVIMIENTO:
			currentAnim = animaciones.at("move");
			break;
		default:
			currentAnim = animaciones.at("idlo");
			break;
		}


	}
}

void Gnomo::Idle(){

	if (!empezado){
		empezado = true;


		SDL_AddTimer(2000u, changeStateCB, this);
		//timers
		//El timer que se activa mas tarde es el changestate
	}
}

void Gnomo::Ataque1() {// Invocar sierras

	if (sierras.size() >= 2) {
		eliminaSierra();
	}

	auto it = sierras.emplace(sierras.begin(), new Sierra(pJuego, getX(), getY(), 0));
	
	SDL_AddTimer(10000u, quitarSierraCB, this);// No se si estará bien aqui.


	/*auto it = myvector.emplace(myvector.begin() + 1, 100);
	myvector.emplace(it, 200);
	myvector.emplace(myvector.end(), 300);*/
}
