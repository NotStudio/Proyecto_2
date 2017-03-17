#include "ZonaAccion.h"
#include "Entidad.h"
#include "checkML.h"
#include "TileInfo.h"

ZonaAccion::ZonaAccion(Juego* punteroJuego): pJuego(punteroJuego)
{
	Puerta p;
	niveles = new vector<Room*>;
	niveles->reserve(4);
	p.DirPuerta = Oeste;
	niveles->push_back(new Room(pJuego, p,niveles));
	niveles->push_back(new Room(pJuego, p, niveles));
	niveles->push_back(new Room(pJuego, p, niveles));


	//niveles.push_back(new Room(pJuego, niveles.at(0)->getArea().x + niveles.at(0)->getArea().w, niveles.at(0)->getArea().y, Direcciones{ false,false, false,true }));
	setRect();
	setNivelActual();
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
	nivelActual = nullptr;
}
void ZonaAccion::draw(){
	for (size_t i = 0; i < niveles->size(); i++)
	{
		niveles->at(i)->render();
	}
	SDL_SetRenderDrawColor(pJuego->getRender(), 0, 255, 0, 255);
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX()/128;
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY()/128;
	SDL_Rect aux = tam;
	aux.x /= 128;
	aux.y /= 128;
	aux.w /= 128;
	aux.h /= 128;
	aux.x += 300;
	aux.y += 300;
	SDL_RenderDrawRect(pJuego->getRender(), &aux);
	SDL_RenderDrawPoint(pJuego->getRender(), pj.x, pj.y);
}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	nivelActual->update();
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
	if (nivelActual != anterior)
		cout << "kek";
	pJuego->getCamera()->setLimite(nivelActual->getArea());
}

SDL_Rect ZonaAccion::getNivelActual() {

	return nivelActual->getArea();

}