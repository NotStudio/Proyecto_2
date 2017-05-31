#include "Cambio.h"
#include "checkML.h"
#include "MenuPG.h"
#include "Jugable.h"
#include "ZonaAccion.h"
#include <typeinfo>

Cambio::Cambio(Juego * juego,vector<Objeto*>& Personajes) : MenuJuego(juego), isSwitchyUnlocked(false)//, pR(nullptr)
{
	pJuego->reproducirEfecto("Multiusos");
	static_cast<ZonaAccion*>(pJuego->getZona())->getNivel()->stop();
	static_cast<Jugable*>(pJuego->getPlayer())->stop();
	if (pJuego->getProgresoNave() >= 4)
		isSwitchyUnlocked = true;
	Fondo = pJuego->getTextura("SelecPersonajeFondo", "idle");
	if (isSwitchyUnlocked) {

		int contY = 0;
		for (auto p : Personajes) {
			insertarBoton(Boton::ILUMINADO, 21 + contY, 33, resume, static_cast<Jugable*>(p)->getId(), "kek");
			contY += 15;
		}
	}
	else {
		insertarBoton(Boton::ILUMINADO, 21, 33, resume, static_cast<Jugable*>(Personajes[0])->getId(), "kek");
	}
	f = 0;
	activo = 0;
	img = pJuego->getTextura(botones[activo]->getNombre(), "idle");

	insertarBoton(Boton::ILUMINADO, 30, 56, resume, "Salir", "kek");
	
	
	//Para añadir los botones

	
}


Cambio::~Cambio()
{
}
void Cambio::draw(){
	MenuJuego::draw();
	
	SDL_Rect rect = { pJuego->getWindow().ancho / 2 - 100, pJuego->getWindow().alto / 5, 150, 150 };
	
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

