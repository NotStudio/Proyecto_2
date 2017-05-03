#pragma once
#include "Crafteo.h"
#include "Boton.h"
class Objetos3 :
	public Crafteo
{

	std::vector <Boton*> botones;

	int activo = 0;

	Juego::Animacion animacion;

	TextoSDL Texto;

public:
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

