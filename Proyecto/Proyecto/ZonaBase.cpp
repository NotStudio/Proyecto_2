#include "ZonaBase.h"
#include "Juego.h"
#include "Room.h"


ZonaBase::ZonaBase(Juego* punteroJuego) :ZonaJuego(punteroJuego), timerTexto_(255)
{
	pJuego->cambiarMusica("base");
	id = "base";
	baseNivel = new Room(pJuego, this, pJuego->getBaseRoom(), {0,0});
	nivelActual = baseNivel;
	pJuego->getCamera()->setLimite(*nivelActual->getArea());
	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::BASE);
	
	static_cast<Jugable*>(pJuego->getPlayer())->setPos(200,50);

	texto1_.LoadFuente(pJuego->getTipografia("Acme____", 20));
	texto2_.LoadFuente(pJuego->getTipografia("Acme____", 20));
	texto3_.LoadFuente(pJuego->getTipografia("Acme____", 20));

	baseNivel->InitRoom();
}


ZonaBase::~ZonaBase()
{
	delete baseNivel;
	baseNivel = nullptr;
}


void ZonaBase::setTextos() {

	texto1_.loadTexto(pJuego->getRender(), frase1_, { 0, 0, 0 });
	texto2_.loadTexto(pJuego->getRender(), frase2_, { 0, 0, 0 });
	texto3_.loadTexto(pJuego->getRender(), frase3_, { 0, 0, 0 });
	texto1_.draw(pJuego->getRender(), pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto - (pJuego->getWindow().alto * 0.2));
	texto2_.draw(pJuego->getRender(), pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto - (pJuego->getWindow().alto * 0.15));
	texto3_.draw(pJuego->getRender(), pJuego->getWindow().ancho * 0.2, pJuego->getWindow().alto - (pJuego->getWindow().alto * 0.1));


}

void ZonaBase::updateTextos()
{
	SDL_Rect* playerPos = pJuego->getPlayer()->getRect();
	if (playerPos->x > 66 && playerPos->x < 270 && playerPos->y > 240 && playerPos->y < 650){
		frase1_ = "Hmmm, parece que tengo algún compañero para ayudarme.";
		frase2_ = "Selector de personaje.";
		frase3_ = "";
	}

	else if (playerPos->x > 560 && playerPos->x < 915 && playerPos->y > 330 && playerPos->y < 710) {
		frase1_ = "Con este mapa podré ir avanzando en las zonas donde puedo conseguir recursos.";
		frase2_ = "Misiones";
		frase3_ = "";
		misiones = true;
	}

	else if (playerPos->x > 1200 && playerPos->x < 1470 && playerPos->y > 66 && playerPos->y < 240) {
		frase1_ = "Esta mesa con herramientas me ayudará a fabricar las piezas para mi nave.";
		frase2_ = "Que no se me olvide guardar las cosas de mi mochila con la tecla 't' en el baúl.";
		frase3_ = "Fabricación de materiales.";
		materiales = true;
	}

	else if (playerPos->x > 1000 && playerPos->x < 1500 && playerPos->y > 650 && playerPos->y < 900) {
		frase1_ = "Vaya, aqui puedo ver la información recogida.";
		frase2_ = "Historia";
		frase3_ = "";
		historia = true;
	}

	else if (playerPos->x > 1600) {
		frase1_ = "Este parece un buen lugar para construir mi nueva nave.";
		frase2_ = "Nave";
		frase3_ = "";
		nave = true;
	}
	else{
		frase1_ = "";
		frase2_ = "";
		frase3_ = "";
	}
}

 SDL_Rect ZonaBase::getNivelActual() {

	 return *nivelActual->getArea();
};
 
 void ZonaBase::draw() {
	 ZonaJuego::draw();
	 setTextos();
 };

 void ZonaBase::update() {
	 updateTextos();
 };