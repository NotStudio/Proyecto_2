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
	stats.velMov = 2;

	/*for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
		animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idlo");*/
	body->SetType(b2_dynamicBody);

	s1 = new Sierra(pJuego, 0, 0, 0);
	s2 = new Sierra(pJuego, 0, 0, 0);
	s3 = new Sierra(pJuego, 0, 0, 0);
	s1->deactivate();
	s2->deactivate();
	s3->deactivate();

	r->nuevoEnemigo(s1);
	r->nuevoEnemigo(s2);
	r->nuevoEnemigo(s3);

	aux = r->getEnemigos();
}


Gnomo::~Gnomo()
{
}

void Gnomo::comportamiento() {

	currentAnim->ActualizarFrame();
	if (!destruido) {
		switch (estado)
		{
		case IDLE:
			Idle();
			break;
		case MOVIMIENTO:
			Movimiento();
			break;
		case ATAQUE1:
			Ataque1();
			break;
		case ATAQUE2:
			Ataque2();
			break;
		case ATAQUE3:
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


uint32 changeStateCB(Uint32 intervalo, void * param){
	static_cast<Gnomo*>(param)->changeState();
	return 0;
}

void Gnomo::Idle(){

	if (!empezado){
		empezado = true;

		stop();
		SDL_AddTimer(2000u, changeStateCB, this);
	}
}





void Gnomo::changeState(){

	empezado = false;
	States viejo = estado;
	if (estado == IDLE) {
		estado = ATAQUE1;
		int rdm = rand() % 2;
		if (rdm == 0) estado = ATAQUE1;
		if (rdm == 1)
		{
			/*if (fase == FASE1)
				estado = ATAQUE2;
			else if (fase == FASE2) {
				rdm = rand() % 2;
				if (rdm == 0) estado = ATAQUE2;
				if (rdm == 1) estado = ATAQUE3;
			}*/
			std::cout << "sdsd";
		}

	}
	//else estado = IDLE;
	/*if (estado != viejo) {
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


	}*/
}


void Gnomo::Movimiento(){

	if (distancia()){

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
		if (velFloat.x > 0) {
			estadoEntidad.mirando = Oeste;
		}
		else if (velFloat.x < 0)
			estadoEntidad.mirando = Este;
		body->SetLinearVelocity(velFloat);
		currentAnim->ActualizarFrame();

	}
	else
	{
		stop();
	}
	
	
}

uint32 quitarSierraCB(Uint32 intervalo, void * param) {
	static_cast<Gnomo*>(param)->eliminaSierra();
	return 0;
}


void Gnomo::Ataque1() {// Invocar sierras
	
	
	
	static_cast<Sierra*>(aux[aux.size() - conts])->activate();
	conts--;
	if (conts == 0){
		conts = 3;
	}

	SDL_AddTimer(1000, quitarSierraCB, this);


	/*if (sierras.size() >= 2) {
		eliminaSierra();
	}
	*/
	
	//auto it = sierras.emplace(sierras.begin(), new Sierra(pJuego, getX(), getY(), 0));

//	SDL_AddTimer(1000, quitarSierraCB, this);// No se si estará bien aqui.


}


void Gnomo::eliminaSierra() {


	static_cast<Sierra*>(aux[aux.size() - contr])->deactivate();
	contr--;
	if (contr == 0)
		contr = 3;
	


}
void Gnomo::Ataque2(){
	//llama a disparo
}

void Gnomo::disparo(string tipo, SDL_Rect posicion, float dirx, float diry, float velocidad){
	//dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaHacha(pJuego, posicion, tipo, velocidad, dirx, diry, stats.daño));
}

void Gnomo::Ataque3(){

}

