#pragma once
#include "HUDObj.h"
#include "TexturasSDL.h"
class HUDText :
	public HUDObj
{
public:
	HUDText();
	HUDText(string texto);
	HUDText(int x1, int y1, int x2, int y2, string texto);
	virtual ~HUDText();
	void cambiaFuente(Fuente * nueva);
	void setText(string txto);
	void draw(int x1, int y1, int x2, int y2);
	void draw();
private:
	TextoSDL * txt;
};

