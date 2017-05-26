#pragma once

#include "Boton.h"
#include "MenuJuego.h"
class Objetos3 :
	public MenuJuego
{
	TexturasSDL * img;

	TextoSDL Texto;
public:
	static bool mecanismoB;
	static bool fibraB;
	static bool combustibleB;
	static bool moduloB;

	Objetos3(Juego* juego);
	virtual ~Objetos3();

	virtual void update();
	virtual void draw();
	static void salir(Juego* pjuego);
	static void combustible(Juego* pjuego);
	static void mecanismo(Juego* pjuego);
	static void fibraCarbono(Juego* pjuego);
	static void moduloComandos(Juego* pjuego);
	static void mensaje(Juego* pjuego);

	void receta(std::string obj);


};

