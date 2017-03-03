#include "Camara.h"
#include <SDL.h>
#include <SDL_image.h>

Camara::Camara() {
	Apuntando = nullptr;
}
Camara::Camara(SDL_Rect * target, int w, int h)
{
	if(target != nullptr)
		Apuntando = target;
	else
		Apuntando = new SDL_Rect({0,0,w,h});
	Centro = { Apuntando->x + Apuntando->w / 2,Apuntando->y + Apuntando->h / 2 };
	plano = { Centro.x-w/2,Centro.y-h/2 ,w ,h };
	ultimoPlano = plano;
}

Camara::~Camara()
{
}

void Camara::setTarget(SDL_Rect *target)
{
	Apuntando = target;
}

void Camara::update()
{
	Centro = { Apuntando->x + Apuntando->w / 2,Apuntando->y + Apuntando->y / 2 };
	plano.x = Centro.x - plano.w / 2;
	plano.y = Centro.y - plano.h / 2;
	if (plano.x <= 0) {
		plano.x = 0;
		Centro.x = plano.w / 2;
	}
	if (plano.y <= 0) {
		plano.y = 0;
		Centro.y = plano.h/2;
	}	
	ultimoPlano = plano;
}

SDL_Rect Camara::getPlano()
{
	return plano;
}
