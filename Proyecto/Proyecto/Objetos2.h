#pragma once
#include "Crafteo.h"
#include "Boton.h"
class Objetos2 :
	public MenuJuego
{
	TexturasSDL * img;
	TextoSDL Texto;

public:
	Objetos2(Juego* juego);
	virtual ~Objetos2();

	virtual void draw();
	static void salir(Juego* pjuego); 
	static void engranaje(Juego* pjuego);
	static void carbono(Juego* pjuego);
	static void engranajes(Juego* pjuego);
	static void tanquePresion(Juego* pjuego);
	static void refinador(Juego* pjuego);
	static void circuito(Juego* pjuego);
	static void bateriaIones(Juego* pjuego);
	static void sensorMov(Juego* pjuego);

	void receta(std::string obj);

};

