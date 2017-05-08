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

	for (auto p : Personajes){
		string n(typeid(*p).name());
		printf(n.c_str());
	}

	activo = 0;

	botones.push_back(new Boton(juego, "button", 400, 400, resume, "Salir"));
	
	//Para añadir los botones

	
}


Cambio::~Cambio()
{

}



void Cambio::resume(Juego * jg){

	static_cast<ZonaAccion*>(jg->getZona())->getNivel()->resume();
	jg->popStateandCamera();
}

