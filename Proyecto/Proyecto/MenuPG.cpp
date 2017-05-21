#include "MenuPG.h"
#include "Boton.h"
#include "Play.h"
#include "Opciones.h"

MenuPG::MenuPG(Juego * juego) :MenuJuego(juego)
{
	Fondo = juego->getTextura("MenuInicio", "idle");
	botones.emplace_back(new Boton(juego, "Button1", 400, 175, playBase,"Jugar","Play the fucking game"));
	botones.emplace_back(new Boton(juego, "Button1", 400, 275, opciones,"Opciones","Configura el juego a tu gusto"));
	botones.emplace_back(new Boton(juego, "Button1", 400, 375, salir,"Salir","Get out of my fucking game"));
}


MenuPG::~MenuPG()
{
	
}


void MenuPG::salir(Juego * jg){
	jg->salir();
}

void MenuPG::cargar(Juego * jg){
}


void MenuPG::opciones(Juego * jg){
	jg->pushState(new Opciones(jg));


}

void MenuPG::playBase(Juego * jg){
	jg->changeState(new Play(jg));
}