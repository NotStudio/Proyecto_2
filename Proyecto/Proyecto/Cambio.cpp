#include "Cambio.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
typedef unsigned int uint;
void Cambio::cambiaMapa(int aux){
	switch (aux){
	case 0:
		mapaAnims = pJuego->getAnimaciones("Tostadora");
		animaciones[0] = mapaAnims.at("idle");
		animaciones[0]->setNumFrames(30);
		mapaAnims.clear();
		break;
	case 1:
		mapaAnims = pJuego->getAnimaciones("OV");
		animaciones[1] = mapaAnims.at("idle");
		animaciones[1]->setNumFrames(30);
		mapaAnims.clear();
		break;
	case 2:
		mapaAnims = pJuego->getAnimaciones("algaba");
		animaciones[2] = mapaAnims.at("idle");
		animaciones[2]->setNumFrames(1);
		mapaAnims.clear();
		break;
	case 3:
		mapaAnims = pJuego->getAnimaciones("Tostadora");
		animaciones[3] = mapaAnims.at("idle");
		animaciones[3]->setNumFrames(30);
		mapaAnims.clear();
		break;
	}

}
Cambio::Cambio(Juego * juego,int actual,int Personajes) : EstadoPG(juego)//, pR(nullptr)
{
	personajes = Personajes;
	//pR->stop();
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();

	activo = actual;
	boton = (new Boton(juego, "boton", juego->getWindow().ancho - 250, juego->getWindow().alto - 130, resume, "Continuar"));
	frame = 0;
	animaciones = vector<Juego::Animacion*>(4, nullptr);
	
	for (uint i = 0; i < animaciones.size(); i++){
		
		cambiaMapa(i);
	}
	PJSelected.LoadFuente(pJuego->getTipografia("a", 70));

	
	//Para añadir los botones

	
}


Cambio::~Cambio()
{
	for (uint i = 0; i < animaciones.size(); i++){
		delete animaciones[i];
		animaciones[i] = nullptr;
	}
	animaciones.clear();
	delete boton;
		boton = nullptr;
		
	mapaAnims.clear();
	
			

	
}



void Cambio::resume(Juego * jg){

	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popStateandCamera();
}
void Cambio::elijeTexto(int i){
	switch (i){
	case 0:
		PJSelected.loadTexto(pJuego->getRender(), "TOASTY");
		break;
	case 1:
		PJSelected.loadTexto(pJuego->getRender(), "PJ2");
		break;
	case 2:
		PJSelected.loadTexto(pJuego->getRender(), "ALGABA MR.MUSCLE");
		break;
	case 3:
		PJSelected.loadTexto(pJuego->getRender(), "PJ4");
		break;


	}
}


void Cambio::draw() {
	const int sizeRect = 160;
	int aux = 0;
	const int MARGEN = (pJuego->getWindow().ancho-sizeRect*5)/5;
	for (uint i = 0; i < 4; i++){
		if (activo == i){
			aux = 50;
			elijeTexto(i);
		}
		else aux = 0;
		animaciones[i]->textura->draw(pJuego->getRender(), SDL_Rect{ pJuego->getWindow().ancho*i / 4 + MARGEN, pJuego->getWindow().alto / 4, sizeRect+aux, sizeRect+aux }, animaciones[i]->currentRect());
		animaciones[i]->ActualizarFrame();
	}
	boton->draw();
	PJSelected.cambiarColor(SDL_Color{ 255, 255, 255, 255 }, pJuego->getRender());
	PJSelected.draw(pJuego->getRender(), (pJuego->getWindow().ancho / 2) - PJSelected.getAncho()/2, pJuego->getWindow().alto * 2 / 3);
	
	//PJSelected.draw(pJuego->getRender(), 250, 250);
}

void Cambio::update() {

	
	if (pJuego->teclaPulsada(SDL_SCANCODE_RIGHT)) {

		if (activo < personajes-1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_LEFT)) {
		if (activo > 0) {
			activo--;
		}
	}
	

	else if (pJuego->inputQuery(SDL_SCANCODE_RETURN)) {
		activar(pJuego);
		boton->accion();




	}
}
