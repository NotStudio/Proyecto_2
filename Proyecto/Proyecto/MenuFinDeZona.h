#ifndef MENUFINDEZONA_H_
#define MENUFINDEZONA_H_
#include "EstadoPG.h"
#include "Boton.h"
#include "Play.h"

class MenuFinDeZona :
	public EstadoPG
{
public:
	MenuFinDeZona(Juego* juego): EstadoPG(juego)
	{
		botones.emplace_back(new Boton(juego, "boton", pJuego->window.ancho/2, 175, goToBase, "Volver A la Base"));
	};
	virtual ~MenuFinDeZona(){
		for (int i = 0; i < botones.size(); i++)
		{
			delete botones[i];
			botones[i] = nullptr;
		}
	};

private:



	int activo = 0;
	std::vector <Boton*> botones;

	static void goToBase(Juego * jg){
		//jg->changeState(new Play(jg));
		jg->reiniciar();
		jg->setZona("ZonaBase");
		Play::setZona();
		jg->popState();

	}

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
	virtual void update(){
		botones[activo]->normal();
		if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

			if (activo < botones.size() - 1) {
				activo++;
			}
		}

		else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
			if (activo > 0) {
				activo--;
			}
		}
		botones[activo]->aumentar();
		if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
			botones[activo]->accion();
		}
	}
	virtual void draw(){
		for (int i = 0; i < botones.size(); i++)
		{
			botones[i]->draw();
		}
	}
};


#endif