#include "ZonaTutorial.h"
#include "Consumible.h"



ZonaTutorial::ZonaTutorial(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon1";

	
	niveles->push_back(new Room(pJuego, this, pJuego->getTutorialRoom(), SDL_Point{ 0,0 }));;
	niveles->at(0)->InitTiles();
	niveles->at(0)->meterEntidades();
	niveles->at(0)->nuevoObjeto(new Pila(punteroJuego, SDL_Rect{800,700,64,64}, "Pila"));
	setNivelActual();

	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::BASE);

	texto_.LoadFuente(pJuego->getTipografia("Acme____", 30));
}


ZonaTutorial::~ZonaTutorial()
{
}

void ZonaTutorial::setTextos() {

	texto_.loadTexto(pJuego->getRender(), "'Utiliza AWSD para controlar mi motor de movimiento'");
	texto_.draw(pJuego->getRender(), 10, 20);




}

void ZonaTutorial::draw() {
	ZonaAccion::draw();
	setTextos();
}