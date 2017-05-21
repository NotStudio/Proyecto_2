#include "HUDImage.h"


HUDImage::HUDImage() : HUDObj(), text(nullptr)
{
	active = false;
}
HUDImage::HUDImage(Juego * pJuego, int x, int y, int x1, int y1, string nText){
	pRend = pJuego->getRender();
	text = pJuego->getTextura(nText, "idle");
	pos = SDL_Rect{ x, y, x1-x, y1-y };
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
	pos = SDL_Rect{ x, y, x1-x, y1-y };
	text->draw(pRend, SDL_Rect{ x, y, x1-x, y1-y });
}
void HUDImage::draw(){
	text->draw(pRend, pos);
}
void HUDImage::draw(int x, int y){
	pos = SDL_Rect{ x, y, text->getAncho(), text->getAlto() };
	text->draw(pRend, pos);
}
