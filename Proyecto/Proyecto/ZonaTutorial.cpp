#include "ZonaTutorial.h"
#include "Consumible.h"
#include "ObjetoHistorico.h"



ZonaTutorial::ZonaTutorial(Juego* punteroJuego) :ZonaAccion(punteroJuego), timerTexto_(255)
{
	pJuego->cambiarMusica("are");
	id = "zon1";

	
	niveles->push_back(new Room(pJuego, this, pJuego->getTutorialRoom(), SDL_Point{ 0,0 }));;
	niveles->at(0)->InitTiles();
	niveles->at(0)->meterEntidades();
	niveles->at(0)->nuevoObjeto(new Pila(punteroJuego, SDL_Rect{800,700,64,64}, "Pila"));
	niveles->at(0)->nuevoObjeto(new ObjetoHistorico(punteroJuego, SDL_Rect{ 800,3500,64,64 }, "Litio", 1));
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
	if (playerPos->y < 400) {
		frase1_ = "Utiliza AWSD para controlar mi motor de movimiento";
		frase2_ = " ";

	}
	else if (playerPos->y > 400 && playerPos->y < 800) {
		frase1_ = "Eso parece una bater�a. Podr�a resultarme �til.";
		frase2_ = "Puede que haya mas objetos repartidos por ah�.";

	}
	else if (playerPos->y > 800 && playerPos->y < 1200) {
		frase1_ = "Las teclas de direcci�n te permiten usar mi sistema de ataque.";
		frase2_ = " ";

	}
	else if (playerPos->y > 1500 && playerPos->y < 2000) {
		frase1_ = "Parece que los algunos CD's se han vuelto hostiles.";
		frase2_ = " ";

	}
	else if (playerPos->y > 2000 && playerPos->y < 2400) {
		frase1_ = "No puedo hacer da�o a esa sierra. Tendr� que esquivarla.";
		frase2_ = " ";

	}
	else if (playerPos->y > 2500 && playerPos->y < 3000) {
		frase1_ = "Algo extra�o est� ocurriendo en la Tierra";
		frase2_ = " ";
	}
	else if (playerPos->y > 3300 && playerPos->y < 3800) {
		frase1_ = "Recoger� materiales para reconstruir la nave." ;
		frase2_ = "Puedes abrir mi sistema de almacenamiento con la tecla I";
	}
	else if(playerPos->y > 3800){
		frase1_ = "Parece que este camino lleva a una f�brica abandonada";
		frase2_ = " ";
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