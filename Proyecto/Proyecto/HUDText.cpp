#include "HUDText.h"


HUDText::HUDText() : txt(nullptr)
{
}
HUDText::HUDText(string texto){

}
void HUDText::draw(int x1, int y1, int x2, int y2){
	pos = SDL_Rect{ x1, y1, x2, y2 };
	txt->draw(pRend, pos.x, pos.y);
}
void HUDText::draw(){
	txt->draw(pRend, pos.x, pos.y);
}


HUDText::~HUDText()
{
	delete txt;
}
