#include "MenuPG.h"
#include "Boton.h"
#include "Play.h"

MenuPG::MenuPG(Juego * juego) :EstadoPG(juego)
{
	botones.emplace_back(new Boton(juego, "boton", 300, 30, salir));
	botones.emplace_back(new Boton(juego, "boton", 300, 300, salir));
	botones.emplace_back(new Boton(juego, "boton", 300, 500, salir));

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
}

void MenuPG::cargar(Juego * jg){
}

void MenuPG::playBase(Juego * jg){
}

void MenuPG::draw(){
	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
}

void MenuPG::update(){
	botones[activo]->normal();
	
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)){

			if (activo < botones.size()-1){
				cout << activo << endl;
				activo++;
			}
		}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
			if (activo > 0){
				activo--;
			}
		}
		botones[activo]->aumentar();
		if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)){
	//Aqui llamas a la funcion que desees ejecutar teniendo en cuenta que hay una variable "activo" que es la que debera elegir la funcion
		pJuego->changeState(new Play(pJuego));

	}
	}