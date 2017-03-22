#include "Jugable.h"
#include "Enemigo.h"
#include "Bala.h"


Jugable::Jugable(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Personaje(punteroJuego, spritePar, objectId)
{
	//Capa de colision.
	fDef.filter.categoryBits = Juego::JUGADOR;
	fDef.filter.maskBits = Juego::ENEMIGO | Juego::ITEM | Juego::ESCENARIO | Juego::ESCENARIO_NOCOL | Juego::AT_ENEMIGO;
	body->CreateFixture(&fDef);
}


Jugable::~Jugable()
{
	SDL_RemoveTimer(timerInmune);
	delete shape;
	shape = nullptr;
}
Uint32 desactivarInmunidad(Uint32 intervalo, void* param) {
	static_cast<Jugable*>(param)->quitarInmunidad();
	//cout << "inmunidad quitada\n";
	return 0;
}
void Jugable::onColisionEnter(Objeto * obj){
	//std::cout << "colision\n";
	if (dynamic_cast<Enemigo*>(obj)|| dynamic_cast<Bala*>(obj)){
		if (!inmune){
			cout << dynamic_cast<Enemigo*>(obj)->getId();
			inmune = true;
			//cout << "inmunidad activada\n";
			stats.vida--;
			pJuego->reproducirEfecto("scream");
			//cout << stats.vida << " vidas tienes\n";
			timerInmune = SDL_AddTimer(350, desactivarInmunidad, this);
		}
	}
}

void Jugable::movControl(){

	Direccion aux;
	int lim = stats.velMov;
	int ac = 0.5 * lim;
	b2Vec2 v = body->GetLinearVelocity();
	
	if (pJuego->inputQuery(SDL_SCANCODE_A)) {
		aux = Oeste;
		if (!(v.x < -lim))
			vel.x -= ac;
	}else if (pJuego->inputQuery(SDL_SCANCODE_D)) {
		aux = Este;
		if (!(v.x > lim)) {
			vel.x += ac;
		}
	}
	else
		aux = SinDir;
	if (pJuego->inputQuery(SDL_SCANCODE_W)) {
		aux = (aux==Este)?NorteEste:(aux==Oeste)?NorteOeste:Norte;
		if (!(v.y < -lim))
			vel.y -= ac;
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_S)) {
		aux = (aux == Este) ? SurEste : (aux == Oeste) ? SurOeste : Sur;
		if (!(v.y > lim))
			vel.y += ac;
	}
	//Para que frene solo y para controlar que no se salga.
	afinarMov(ac, lim, aux);
}

void Jugable::afinarMov(int const & ac, int const & lim,Direccion const & aux) {

	//Para que pare solo.
	if (aux == Norte || aux == Sur || aux == SinDir) {
		if (vel.x != 0) {
			if (vel.x > 0)
				vel.x -= ac;
			else
				vel.x += ac;
		}
	}

	if (aux == Este || aux == Oeste || aux == SinDir) {
		if (vel.y != 0) {
			if (vel.y > 0)
				vel.y -= ac;
			else
				vel.y += ac;
		}
	}
	//Para que no se salga de los límites.
	if (vel.x >= lim || vel.x <= -lim) {
		if (vel.x > 0)
			vel.x = lim;
		else
			vel.x = -lim;
	}
	if (vel.y >= lim || vel.y <= -lim) {
		if (vel.y > 0)
			vel.y = lim;
		else
			vel.y = -lim;
	}
	if (estadoEntidad.animacionActual != NoAnim) {
		if (estadoEntidad.animacionActual !=Ataque)
		{
		 (aux != estadoEntidad.mirando&&aux != SinDir) ? estadoEntidad.mirando = aux : aux;
		}
		EstadoAnimacion aux1;
		(aux != SinDir) ? aux1 = Walk : aux1 = Idle;
		(aux1 != estadoEntidad.animacionActual) ? estadoEntidad.animacionActual = aux1 : aux1;
	}
}

void Jugable::move() {
	movControl();
	//Movimiento;
	b2Vec2 velFloat;
	velFloat.x = (float32)vel.x / 40;
	velFloat.y = (float32)vel.y / 40;
	body->SetLinearVelocity(velFloat);
}

void Jugable::update() {
	move();
	Personaje::update();
}