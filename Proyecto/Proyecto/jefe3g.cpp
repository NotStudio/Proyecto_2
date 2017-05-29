#include "jefe3g.h"


jefe3g::jefe3g(Juego* punteroJuego, int x, int y) : Enemigo(punteroJuego, { x, y, 96, 96 }, "gnomo", 1000)
{
	fDef.filter.categoryBits = Juego::ENEMIGO;
	fDef.filter.maskBits = Juego::JUGADOR | Juego::ESCENARIO | Juego::ENEMIGO | Juego::ESCENARIO_NOCOL | Juego::AT_JUGADOR;
	body->CreateFixture(&fDef);

	estado = IDLE;
	fase = FASE1;

	stats.da�o = 5;
	stats.vida = 700;
	stats.velMov = 2;

	/*for (unordered_map<string, Juego::Animacion*>::iterator i = animaciones.begin(); i != animaciones.end(); i++)
	{
	animaciones[i->first]->setNumFrames(30);
	}
	currentAnim = animaciones.at("idlo");*/
	body->SetType(b2_dynamicBody);

	/*for (int i = 1; i < 4; i++){
		static_cast <Sierra*>(static_cast<ZonaJuego*>(pJuego->getZona())->getRoomActual()->getEnemigos()[i])->deactivate();
	}
	*/

}


jefe3g::~jefe3g()
{
	SDL_RemoveTimer(est);
	SDL_RemoveTimer(mov);
	SDL_RemoveTimer(att1);
	

}

/////////////////////////////////////////

Uint32 jefe3g::changeStateCB(Uint32 intervalo, void * param){
	static_cast<jefe3g*>(param)->changeState();
	return 0;
}

Uint32 jefe3g::changeIdleCB(Uint32 intervalo, void * param){
	static_cast<jefe3g*>(param)->estar();
	return 0;
}

Uint32 jefe3g::quitarSierraCB(Uint32 intervalo, void * param) {
	static_cast<jefe3g*>(param)->eliminaSierra();
	return 0;
}

////////////////////////////////////////

void jefe3g::changeState(){
	empezado = false;
	viejo = estado;
	/*if (estado == IDLE || estado == MOVIMIENTO){
		int rdm = rand() % 3;
		if (rdm == 0 )
			estado = MOVIMIENTO;
		if (rdm == 2 || rdm == 1)
		{
			if (fase == FASE1){
				int rmg = rand() % 2;
				if (rmg == 0)
					estado = ATAQUE1;
				if (rmg == 1)
					estado = ATAQUE2;
			}
			if (fase == FASE2) {
				rdm = rand() % 3;
				if (rdm == 0)
					estado = ATAQUE1;
				if (rdm == 1)
					estado = ATAQUE2;
				if (rdm == 2)
					estado = ATAQUE3;
			}

		}
	}*/
	estado = ATAQUE1;
}




////////////////////////////////
void jefe3g::comportamiento(){

	std::cout << pos.x << "    " << pos.y << "\n";

	if (ewwe == 0)
	{
		sierras = static_cast<ZonaJuego*>(pJuego->getZona())->getRoomActual()->getEnemigos();
	
		for (int i = 1; i < sierras.size(); i++){
			if (sierras[i] != nullptr){
				static_cast<Sierra*>(sierras[i])->deactivate();
			}
			else {
				for (int i = 1; i < 4; i++){
					static_cast<Sierra*>(sierras[i])->deactivate();

				}
		}
		ewwe++;
	}
	
	}

	if (!destruido) {
		switch (estado)
		{
		case IDLE:
			estar();
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
		default:
			break;
		}
	}
}

void jefe3g::onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2){
	if (contactObject != nullptr) {
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::AT_JUGADOR) {
			stats.vida--;
			//stats.vida--; Hay que fixearlo...

			//if (stats.vida == 15) fase = FASE2;// Ser�a la mitad de la vida...
			if (stats.vida <= 0) muerte();
		}
	}
}


///////////////////////////////////////////////////////////////////
void jefe3g::estar(){
	if (!empezado){
		empezado = true;
		stop();
		est = SDL_AddTimer(2000u, changeStateCB, this);
	}

}



void jefe3g::Movimiento(){
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

		mov = SDL_AddTimer(10000u, changeIdleCB, this);
	}
}


////////////////////////////////////////////////////////////////////////////
void jefe3g::Ataque1(){

	if (conts >= 4){
		conts = 1;
	}
	if (sierras[conts] != nullptr){
		static_cast<Sierra*>(sierras[conts])->activate();
		static_cast<Sierra*>(sierras[conts])->setPos(pos.x, pos.y);
		conts++;
	}

	att1 = SDL_AddTimer(10000, quitarSierraCB, this);
	
	estado = IDLE;
	



	
}


void jefe3g::eliminaSierra(){
	if (contr >= 4){
		contr = 1;
	}
	if (sierras[contr] != nullptr){
		static_cast<Sierra*>(sierras[contr])->deactivate();
		contr++;
	}
	else {
		for (int i = 1; i < 4; i++){
			static_cast<Sierra*>(sierras[i])->deactivate();

		}
	}

	SDL_RemoveTimer(att1);

}

////////////////////////////////////////////////////////////////////////////
void jefe3g::Ataque2(){
	disparo();
	
	estado = IDLE;

}


void jefe3g::disparo(){
	jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 posJug = b2Vec2(jugx / PPM, jugy / PPM);
	b2Vec2 vecDir = posJug - pos;

	dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaHacha(pJuego, SDL_Rect{ getX(), getY() + 150, 24, 24 }, vecDir.x, vecDir.y));

}


/////////////////////////////////////////////////////////////////////////////
void jefe3g::Ataque3(){
	
		jugx = static_cast<Entidad*>(pJuego->getPlayer())->getX();
		jugy = static_cast<Entidad*>(pJuego->getPlayer())->getY();
		b2Vec2 posJug = b2Vec2(jugx / PPM, jugy / PPM);
		b2Vec2 vecDir = posJug - pos;
		dynamic_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->nuevaBala(new BalaMultiple(pJuego, SDL_Rect{ getX(), getY() + 150, 24, 24 }, vecDir.x, vecDir.y));
		
	estado = IDLE;
}