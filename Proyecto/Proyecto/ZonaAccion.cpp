#include "ZonaAccion.h"
#include "Entidad.h"
#include "checkML.h"
#include "TileInfo.h"

ZonaAccion::ZonaAccion(Juego* punteroJuego): pJuego(punteroJuego)
{
	Puerta p;
	p.DirPuerta = Puerta::Direcciones::Oeste;
	niveles.push_back(new Room(pJuego, p));
	p.DirPuerta = Puerta::Direcciones::Oeste;
	niveles.push_back(new Room(pJuego,p,&niveles[0]->getSalida()));
	p.DirPuerta = Puerta::Direcciones::Sur;
	niveles.push_back(new Room(pJuego, p, &niveles[1]->getSalida()));
	niveles.push_back(new Room(pJuego, p, &niveles[2]->getSalida()));
	//niveles.push_back(new Room(pJuego, niveles.at(0)->getArea().x + niveles.at(0)->getArea().w, niveles.at(0)->getArea().y, Direcciones{ false,false, false,true }));
	nivelActual = niveles.at(0);
}


ZonaAccion::~ZonaAccion()
{
	for (size_t i = 0; i < niveles.size(); i++)
	{
		delete niveles[i];
		niveles[i] = nullptr;
	}
	nivelActual = nullptr;
}

void ZonaAccion::draw(){
	/*
	for (size_t i = 0; i < niveles.size(); i++)
	{
		niveles[i]->render();
	}
	*/
	nivelActual->render();

}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	nivelActual->update();
}

void ZonaAccion::setNivelActual(){
	//Actualizamos el parametro que indica el nivel en el que estamos
	//y  se lo notificamos a la cámara.
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	int i = 0;
	bool stop = false;
	while (i < niveles.size()){
		if (niveles[i]->dentroRoom(&pj)){
			nivelActual = niveles[i];
		}
		else {
			niveles[i]->stop();
		}
		i++;
	}
	pJuego->getCamera()->setLimite(nivelActual->getArea());
}

SDL_Rect ZonaAccion::getNivelActual() {

	return nivelActual->getArea();

}