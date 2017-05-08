#include "Cambio.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
#include <typeinfo>

Cambio::Cambio(Juego * juego,vector<Objeto*>& Personajes) : MenuJuego(juego)//, pR(nullptr)
{
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();
	int contY = 0;

	for (auto p : Personajes){
		botones.emplace_back(new Boton(juego, "button", 20, 50 + 50*contY, resume, static_cast<Jugable*>(p)->getId()));
		contY++;
	}
	f = 0;
	activo = 0;
	img = pJuego->getTextura(botones[activo]->getNombre(), "idle");

	botones.push_back(new Boton(juego, "button", 400, 400, resume, "Salir"));
	
	//Para añadir los botones

	
}


Cambio::~Cambio()
{
}
void Cambio::draw(){
	MenuJuego::draw();
	SDL_Rect rect = { 400, 100, 150, 150 };
	
	SDL_Rect frame = { f*img->getAncho() / 30, 0, img->getAncho() / 30 , img->getAlto() };
	img->draw(pJuego->getRender(), rect, &frame);
}

void Cambio::update(){
	MenuJuego::update();
	if (botones[activo]->getNombre() != "Salir"){
		TexturasSDL * prev = img;
		img = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		if (prev == img){
			f++;
			if (f > 29)
				f = 0;

		}
		else
			f = 0;
	}

}


void Cambio::resume(Juego * jg){

	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popStateandCamera();
}

