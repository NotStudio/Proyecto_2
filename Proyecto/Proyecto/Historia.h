#pragma once
#include "MenuJuego.h"
#include "EstadoPG.h"

class Historia : public MenuJuego
{
public:
	Historia(Juego* pJuego);
	virtual ~Historia();


protected:
	static void salir(Juego * jg);
	static void marcoHis(Juego* jg);
	static void toastyHis(Juego* jg);


};

