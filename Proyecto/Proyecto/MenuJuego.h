#pragma once
#include "EstadoPG.h"
#include "Boton.h"
class MenuJuego :
	public EstadoPG
{
public:
	MenuJuego(Juego* juego);
	~MenuJuego();
	virtual void update();
	virtual void draw();
	virtual void handleEvent(const SDL_Event& event);
	enum MenuState
	{
		STARTING=0,STARTED=1
	};
protected:
	MenuState MenuState_;
	CuadroDeTexto kek;
	TextoSDL ayuda;
	void updateBotones();
	int activo = 0;
	vector<Boton*>botones;
	TexturasSDL*Fondo=nullptr;
	Uint8 alpha=0;
};

