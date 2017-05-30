#ifndef MENUFINDEZONA_H_
#define MENUFINDEZONA_H_
#include "MenuJuego.h"
#include "Boton.h"
#include "Play.h"

class MenuFinDeZona :
	public MenuJuego
{
public:
	MenuFinDeZona(Juego* juego): MenuJuego(juego)
	{
		Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
		insertarBoton(Boton::MECANICO, 32, 32, goToBase, "Volver A la Base");
	};
	virtual ~MenuFinDeZona(){};

private:
	
	static void goToBase(Juego * jg){
		//jg->changeState(new Play(jg));
		jg->reiniciar();
		jg->setZona("ZonaBase");
		Play::setZona();
		jg->popState();

	}
};


#endif