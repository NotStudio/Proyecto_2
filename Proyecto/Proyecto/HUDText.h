#pragma once
#include "HUDObj.h"
#include "TexturasSDL.h"
class HUDText :
	public HUDObj
{
public:
	HUDText();
	HUDText(Juego * pJuego, string texto);
	HUDText(Juego * pJuego,int x1, int y1, int x2, int y2, string texto);
	HUDText(Juego * pJuego, string texto, int tam, SDL_Color color = SDL_Color{ 0, 0, 0 }, string fuente = "");
	virtual ~HUDText();
	void cambiaFuente(string fuente);
	void setTexto(string txto);
	void setColor(SDL_Color color);
	void draw(int x1, int y1, int x2, int y2);
	void draw();
	void setTamanyo(int tam);
	inline void setPos(int x1, int y1, int x2, int y2){
		pos = SDL_Rect{ x1, y1, x2, y2 };
	}
private:
	TextoSDL * txt;
	string texto;
	SDL_Color color;
	string nFuente;
	Fuente * fuente;
	int tam;
};

