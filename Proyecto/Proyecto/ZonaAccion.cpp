#include "ZonaAccion.h"
#include "checkML.h"
#include "TileInfo.h"

ZonaAccion::ZonaAccion(Juego* punteroJuego): ZonaJuego(punteroJuego)
{
	//Inicializamos el array de habitaciones
	niveles = new vector<Room*>;
	niveles->reserve(25);
	//Cambiamos el estado del jugador
	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::JUGANDO);
	//Cambiamos su posición al centro del nivel inicial.
	static_cast<Jugable*>(pJuego->getPlayer())->setPos(50,50);
}


ZonaAccion::~ZonaAccion()
{
	for (size_t i = 0; i < niveles->size(); i++)
	{
		delete niveles->at(i);
		niveles->at(i) = nullptr;
	}
	delete niveles;
	niveles = nullptr;
	
}
void ZonaAccion::draw(){
	ZonaJuego::draw();

	//Descomentar para ver la disposición de las habitaciones

	for (size_t i = 0; i < niveles->size(); i++)
	{
		SDL_Rect aux = niveles->at(i)->getArea();
		aux.x /= 64; aux.y /= 64; aux.h /= 64; aux.w /= 64; aux.x += 100; aux.y += 100;
		SDL_RenderDrawRect(pJuego->getRender(), &aux);
	}
}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	ZonaJuego::update();
}

void ZonaAccion::setNivelActual(){
	//Actualizamos el parametro que indica el nivel en el que estamos
	//y  se lo notificamos a la cámara.
	Room * anterior = nivelActual;
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	int i = 0;
	bool stop = false;
	for (size_t i = 0; i < niveles->size(); i++)
	{
		if (niveles->at(i)->dentroRoom(&pj)) nivelActual = niveles->at(i);
		else niveles->at(i)->stop();
	}
	if (nivelActual != anterior) {
		cout << "Cambio Nivel\n";
		if (!nivelActual->isEmpty())
			cout << "Habitación con Enemigos. *Puertas cerradas*";
	}
	pJuego->getCamera()->setLimite(nivelActual->getArea());
}
