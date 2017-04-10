#include "ZonaDesguace.h"


ZonaDesguace::ZonaDesguace(Juego* punteroJuego) :ZonaAccion(punteroJuego)
{
	pJuego->cambiarMusica("are");
	id = "zon2";
	
	
	
	//Metemos los niveles 
	for (size_t i = 0; i < 2; i++)// i = número de 'pisos'
	{
		//Metemos un nivel neutro (ini) por cada X niveles normales
		niveles->push_back(new Room(pJuego, niveles, this, "Ini"));
		//j = niveles por piso
		for (size_t j = 0; j < 2; j++) {
			niveles->push_back(new Room(pJuego, niveles, this, "Normal"));
		}

		//Aquí hacer el aumento de dificultad. Una idea es ponerlo por parámetro en la constructora dd Room. Ya veremos
	}
	//Metemos el nivel del boss
	niveles->push_back(new Room(pJuego, niveles, this, "Boss"));
	setRect();
	setNivelActual();
}


ZonaDesguace::~ZonaDesguace()
{
}
