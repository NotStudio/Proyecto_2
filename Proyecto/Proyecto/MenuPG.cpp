#include "MenuPG.h"
#include "Boton.h"
#include "Play.h"

MenuPG::MenuPG(Juego * juego) :EstadoPG(juego)
{
	botones.emplace_back(new Boton(juego, "boton", 300, 250, playBase,"Jugar"));
	botones.emplace_back(new Boton(juego, "boton", 300, 350, salir,"Opciones"));
	botones.emplace_back(new Boton(juego, "boton", 300, 450, salir,"Salir"));
}


MenuPG::~MenuPG()
{
	for (int i = 0; i < botones.size(); i++)
	{
		delete botones[i];
		botones[i] = nullptr;
	}
}


void MenuPG::salir(Juego * jg){
	cout << "algaba Becario\n";
}

void MenuPG::cargar(Juego * jg){
}

void MenuPG::playBase(Juego * jg){
	jg->changeState(new Play(jg));
}

void MenuPG::draw(){
	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void MenuPG::update() {
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