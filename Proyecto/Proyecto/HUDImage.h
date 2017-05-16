#pragma once
#include "HUDObj.h"
#include "TexturasSDL.h"
class HUDImage :
	public HUDObj
{
public:
	HUDImage();
	HUDImage(Juego * pJuego, int x, int y, int x1, int x2, string nText);
	HUDImage(Juego * pJuego, string nText);
	virtual ~HUDImage();
	void draw();
	void draw(int x, int y, int x1, int y1);
	void loadImage(string image);
private:
	TexturasSDL* text;
};

