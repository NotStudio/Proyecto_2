#include "HUDImage.h"


HUDImage::HUDImage() : HUDObj(), text(nullptr)
{
	active = false;
}
HUDImage::HUDImage(Juego * pJuego, int x, int y, int x1, int y1, string nText){
	pRend = pJuego->getRender();
	text = pJuego->getTextura(nText, "idle");
	pos = SDL_Rect{ x, y, x1, y1 };
	active = true;
}

HUDImage::HUDImage(Juego * pJuego, string nText){
	pRend = pJuego->getRender();
	text = pJuego->getTextura(nText, "idle");
	pos = SDL_Rect{ 0, 0, text->getAncho(), text->getAlto() };
	active = true;
}
HUDImage::~HUDImage()
{
	delete text;
}
void HUDImage::draw(int x, int y, int x1, int y1){
	pos = SDL_Rect{ x, y, x1, y1 };
	text->draw(pRend, SDL_Rect{ x, y, x1, y1 });
}
void HUDImage::draw(){
	text->draw(pRend, pos);
}
