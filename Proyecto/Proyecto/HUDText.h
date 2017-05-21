#pragma once
#include "HUDObj.h"
#include "TexturasSDL.h"
class HUDText :
	public HUDObj
{
public:
	HUDText();
	HUDText(Juego * pJuego, string texto);
	HUDText(Juego * pJuego,int x1, int y1, string nFuente);
	HUDText(Juego * pJuego, int x1, int y1, int x2, int y2, string nFuente);
	HUDText(Juego * pJuego, string texto, int tam, SDL_Color color = SDL_Color{ 0, 0, 0 }, string fuente = "");
	virtual ~HUDText();
	void cambiaFuente(string fuente);
	void setTexto(string txto);
	void setColor(SDL_Color color);
	void draw();
	void draw(string texto);
	void draw(int x, int y);
	void draw(int x, int y, int x1, int y1);
	void setTamanyo(int tam);
	inline void setPos(int x1, int y1){
		pos = SDL_Rect{ x1, y1, txt->getAncho(), txt->getAlto() };
	}
private:
	TextoSDL * txt;
	string texto;
	SDL_Color color;
	string nFuente;
	Fuente * fuente;
	int tam;
};

