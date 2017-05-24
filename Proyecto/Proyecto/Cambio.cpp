#include "Cambio.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
#include <typeinfo>

Cambio::Cambio(Juego * juego,vector<Objeto*>& Personajes) : MenuJuego(juego)//, pR(nullptr)
{
	pJuego->reproducirEfecto("Multiusos");
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();
	int contY = 0;
	Fondo = pJuego->getTextura("SelecPersonajeFondo", "idle");

	for (auto p : Personajes){
		botones.emplace_back(new BotonIluminado(pJuego, 30 + 50 * contY, 300, resume, static_cast<Jugable*>(p)->getId()));
		contY += 5;
	}
	f = 0;
	activo = 0;
	img = pJuego->getTextura(botones[activo]->getNombre(), "idle");

	botones.push_back(new BotonIluminado(pJuego, 300, 500, resume, "Salir"));
	
	//Para añadir los botones

	
}


Cambio::~Cambio()
{
}
void Cambio::draw(){
	MenuJuego::draw();
	SDL_Rect rect = { 315, 100, 150, 150 };
	
	SDL_Rect frame = { 0, 0, img->getAncho() / 30 , img->getAlto() };
	img->draw(pJuego->getRender(), rect, &frame);
}

void Cambio::update(){
	MenuJuego::update();
	if (botones[activo]->getNombre() != "Salir"){
		pJuego->setActivo(activo);
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

