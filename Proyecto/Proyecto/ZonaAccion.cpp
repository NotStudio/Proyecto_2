#include "ZonaAccion.h"
#include "Entidad.h"
#include "checkML.h"
#include "TileInfo.h"
bool solapa(SDL_Rect const & a, SDL_Rect const & b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a.x; rightA = a.x + a.w; topA = a.y; bottomA = a.y + a.h;
	leftB = b.x; rightB = b.x + b.w; topB = b.y; bottomB = b.y + b.h;
	if (bottomA <= topB) { return false; } if (topA >= bottomB) { return false; } if (rightA <= leftB) { return false; } if (leftA >= rightB) { return false; }
	return true;
}
ZonaAccion::ZonaAccion(Juego* punteroJuego): pJuego(punteroJuego)
{
	Puerta p ;
	p.posicion = { 0, 0, 0, 0 };
	niveles = new vector<Room*>;
	niveles->reserve(25);
	

	niveles->push_back(new Room(pJuego,  niveles));
	size_t k = sizeof(niveles->at(0));

	//niveles.push_back(new Room(pJuego, niveles.at(0)->getArea().x + niveles.at(0)->getArea().w, niveles.at(0)->getArea().y, Direcciones{ false,false, false,true }));
	for (size_t i = 0; i < niveles->size(); i++)
	{
		for (size_t j = i+1 ; j < niveles->size(); j++)
		{
			if (solapa(niveles->at(i)->getArea(), niveles->at(j)->getArea())){
				cout << "kek";
			}
		}
	}
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