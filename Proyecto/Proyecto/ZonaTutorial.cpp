#include "ZonaTutorial.h"
#include "Consumible.h"
#include "ObjetoHistorico.h"
#include "ObjetoClave.h"


ZonaTutorial::ZonaTutorial(Juego* punteroJuego) :ZonaAccion(punteroJuego), timerTexto_(255)
{
	id = "zon1";

	
	niveles->push_back(new Room(pJuego, this, pJuego->getTutorialRoom(), SDL_Point{ 0,0 }));;
	niveles->at(0)->InitTiles();
	niveles->at(0)->meterEntidades();
	niveles->at(0)->nuevoObjeto(new Pila(punteroJuego, SDL_Rect{800,700,64,64}, "Pila"));
	niveles->at(0)->nuevoObjeto(new ObjetoHistorico(punteroJuego, SDL_Rect{ 800,3500,64,64 }, "Litio", 1));
	niveles->at(0)->nuevoObjeto(new ObjetoClave(punteroJuego, SDL_Rect{ 800, 3800, 64, 64 }));
	setNivelActual();

	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::BASE);

	texto1_.LoadFuente(pJuego->getTipografia("Acme____", 20));
	texto2_.LoadFuente(pJuego->getTipografia("Acme____", 20));
	frase1_ = "Utiliza AWSD para controlar mi motor de movimiento";
	frase2_ = " ";
}


ZonaTutorial::~ZonaTutorial()
{
}

void ZonaTutorial::setTextos() {
	
	texto1_.loadTexto(pJuego->getRender(), frase1_, { 0,0,0 });
	texto2_.loadTexto(pJuego->getRender(), frase2_, { 0,0,0 });
	texto1_.draw(pJuego->getRender(), pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto - (pJuego->getWindow().alto * 0.2));
	texto2_.draw(pJuego->getRender(), pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto - (pJuego->getWindow().alto * 0.15));
	
}

void ZonaTutorial::updateTextos()
{
	SDL_Rect* playerPos = pJuego->getPlayer()->getRect();
	if (playerPos->y < 500 && !AWSD) {
		frase1_ = "Utiliza AWSD para controlar mi movimiento.";
		frase2_ = " ";
		AWSD = true;

	}
	else if (playerPos->y > 500 && playerPos->y < 800 && !bateria) {
		frase1_ = "Eso parece una batería. Podría resultarme útil.";
		frase2_ = "Puede que haya mas objetos repartidos por ahí.";
		bateria = true;
	}
	else if (playerPos->y > 800 && playerPos->y < 1200 && !ataque) {
		frase1_ = "Las teclas de dirección te permiten usar mi sistema de ataque.";
		frase2_ = " ";
		ataque = true;
	}
	else if (playerPos->y > 1300 && playerPos->y < 1900 && ! CDS) {
		frase1_ = "Parece que los algunos CD's se han vuelto hostiles.";
		frase2_ = " ";
		CDS = true;
	}
	else if (playerPos->y > 1900 && playerPos->y < 2300 && !sierra) {
		frase1_ = "No puedo hacer daño a esa sierra. Tendré que esquivarla.";
		frase2_ = " ";
		sierra = true;
	}
	else if (playerPos->y > 2500 && playerPos->y < 3000 && !ocurriendo) {
		frase1_ = "Algo extraño está ocurriendo.";
		frase2_ = " ";
		ocurriendo = true;
	}
	else if (playerPos->y > 3300 && playerPos->y < 3600 && !materiales) {
		frase1_ = "Recogeré materiales para reconstruir la nave." ;
		frase2_ = "Puedes abrir mi sistema de almacenamiento con la tecla I.";
		materiales = true;
	}
	else if(playerPos->y > 3600){
		frase1_ = "Parece que este camino lleva a una fábrica abandonada.";
		frase2_ = "¿Y esta tarjeta SD? ¿Para qué servirá? ";
	}
}

void ZonaTutorial::update() {
	ZonaAccion::update();
	updateTextos();
}

void ZonaTutorial::draw() {
	ZonaAccion::draw();
	setTextos();
}