#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon2";

	firstRoom_ = new Room(pJuego, niveles, this, "Ini");
	//Metemos los niveles 
	//Metemos un nivel neutro (ini) por cada X niveles normales
	niveles->push_back(firstRoom_);
	//j = niveles por piso
	for (size_t j = 0; j < 2; j++) {
		niveles->push_back(new Room(pJuego, niveles, this, "Normal"));
	}
	lastRoom_ = new Room(pJuego, niveles, this, "Ini");
	niveles->push_back(lastRoom_);
	//Aquí hacer el aumento de dificultad. Una idea es ponerlo por parámetro en la constructora dd Room. Ya veremos

	//Metemos el nivel del boss
	niveles->push_back(new Room(pJuego, niveles, this, "Boss"));
	setRect();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
