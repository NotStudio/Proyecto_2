#include "ZonaAccion.h"


ZonaAccion::ZonaAccion(Juego* punteroJuego) :ZonaJuego(punteroJuego)
{
}


ZonaAccion::~ZonaAccion()
{
	nivelActual = nullptr;
}

void ZonaAccion::draw(){

	nivelActual->render();




}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	
	


}

void ZonaAccion::setNivelActual(){
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	int i = 0;
	bool stop = false;
	while (!stop && i < niveles.size()){
		if (niveles[i]->dentroRoom(&pj)){
			stop = true;
			nivelActual = niveles[i];
		}
		i++;
	}
}