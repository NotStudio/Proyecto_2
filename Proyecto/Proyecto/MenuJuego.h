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
	void insertarBoton(Boton::ButtonType type, Uint8 factorX, Uint8 factorY, Boton::CallBack_t * accion, string nombre, string descripcion="no hay descripcion");
	MenuState MenuState_;
	CuadroDeTexto kek;
	TextoSDL ayuda;
	void updateBotones();
	int activo = 0;
	vector<Boton*>botones;
	TexturasSDL*Fondo=nullptr;
	Uint8 alpha=0;
	int fx;
	int fy;
};

