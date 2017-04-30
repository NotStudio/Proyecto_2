#include "Jugable.h"
#include "Enemigo.h"
#include "BalaEnemiga.h"
#include "BalaAceite.h"
#include "Bala.h"


Jugable::Jugable(Juego* punteroJuego, SDL_Rect spritePar, string objectId):Personaje(punteroJuego, spritePar, objectId)
{
	//Capa de colision.
	fDef.filter.categoryBits = Juego::JUGADOR;
	fDef.filter.maskBits = Juego::ENEMIGO | Juego::ITEM | Juego::ESCENARIO | Juego::ESCENARIO_NOCOL | Juego::AT_ENEMIGO;
	body->CreateFixture(&fDef);
	
	state = BASE;
}


Jugable::~Jugable()
{
	SDL_RemoveTimer(timerInmune);
	
}
Uint32 desactivarInmunidad(Uint32 intervalo, void* param) {
	static_cast<Jugable*>(param)->quitarInmunidad();
	//cout << "inmunidad quitada\n";
	return 0;
}
Uint32 velocidadNormal(Uint32 intervalo, void* param){
	static_cast<Jugable*>(param)->velocidad();
	return 0;
}
void Jugable::onColisionEnter(Objeto* obj, b2Body* b1, b2Body* b2){
	//std::cout << "colision\n";

	if (obj != nullptr){
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_ENEMIGO ||
			b2->GetFixtureList()->GetFilterData().categoryBits == Juego::ENEMIGO){
			if (b1->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR){
				if (dynamic_cast<BalaAceite*>(obj)){
					if (!ralentizado){
						ralentizado = true;
						stats.velMov /= 4;
						timerRalentizado = SDL_AddTimer(550, velocidadNormal, this);
					}
				}

				else if (!inmune){
					inmune = true;
					//Si el objeto es una bala, nos hatrá el danyo estipulado
					if (dynamic_cast<BalaEnemiga*>(obj) != nullptr){
						stats.vida -= static_cast<BalaEnemiga*>(obj)->getDanyo();
					}
					//Si no, deducimos que estamos colisionando con el cuerpo de un enemigo, 
					//por lo que restamos una sola vida.
					else stats.vida--;

					if (stats.vida < 0)stats.vida = 0;
					pJuego->reproducirEfecto("scream");
	
					timerInmune = SDL_AddTimer(350, desactivarInmunidad, this);
				}


			}
		}
	}
}


void Jugable::movControl(){

	Direccion aux = SinDir;
	int lim = stats.velMov;
	int ac = 0.5 * lim;
	b2Vec2 v = body->GetLinearVelocity();


	//Escaneo de teclas


	if (pJuego->inputQuery(SDL_SCANCODE_A)){
		aux = Oeste;

	}
	else if (pJuego->inputQuery(SDL_SCANCODE_D)){
		aux = Este;
	}


	if (pJuego->inputQuery(SDL_SCANCODE_W)){
		if (aux == Este)aux = NorteEste;
		else if (aux == Oeste) aux = NorteOeste;
		else aux = Norte;
	}
	else if (pJuego->inputQuery(SDL_SCANCODE_S)){
		if (aux == Este) aux = SurEste;
		else if (aux == Oeste)aux = SurOeste;
		else aux = Sur;
	}



	//Segun la direccion en que queramos ir, sumamos una cantidad u otra en 
	//cada eje.
	switch (aux){
	case Norte:
		if (!(v.y < -lim))
			vel.y -= ac;
		break;
	case Sur:
		if (!(v.y > lim))
			vel.y += ac;
		break;
	case Este:
		if (!(v.x > lim))
			vel.x += ac;
		break;
	case Oeste:
		if (!(v.x < -lim))
			vel.x -= ac;
		break;
	case NorteEste:
		//0.785398 = 45º en radianes
		if (!(v.y < -lim))
			vel.y -= ac*sin(0.785398);
		if (!(v.x > lim))
			vel.x += ac*cos(0.785398f);
		break;
	case NorteOeste:
		if (!(v.y < -lim))
			vel.y -= ac*sin(0.785398);
		if (!(v.x < -lim))
			vel.x -= ac*sin(0.785398);
		break;
	case SurEste:
		if (!(v.y > lim))
			vel.y += ac*sin(0.785398);
		if (!(v.x > lim))
			vel.x += ac*sin(0.785398);

		break;
	case SurOeste:
		if (!(v.y > lim))
			vel.y += ac*sin(0.785398);
		if (!(v.x < -lim))
			vel.x -= ac*sin(0.785398);

		break;
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

void Jugable::stop() {
	body->SetLinearVelocity(b2Vec2{ 0, 0 });
}