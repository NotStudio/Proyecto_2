#include "Camara.h"
#include <SDL.h>
#include <SDL_image.h>
#include "checkML.h"
#include <iostream>
Camara::Camara() {
	Apuntando = nullptr;
}
Camara::Camara(SDL_Rect * target, int w, int h)
{
	anguloCamara = 0;
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
	SDL_RemoveTimer(TemporazidorEfecto);
}

void Camara::setTarget(SDL_Rect *target)
{
	Apuntando = target;
}

void Camara::update()
{
	Centro = { Apuntando->x + Apuntando->w / 2,Apuntando->y + Apuntando->h/ 2 };
	plano.x = Centro.x - plano.w / 2;
	plano.y = Centro.y - plano.h / 2;
	if (BloquearEjeX) {
		plano.x = minX - (plano.w - (maxX - minX)) / 2;
		Centro.x = plano.x + plano.w / 2;
	} 
	else {
		bool izq = false, der = false;
		if (plano.x < minX) {
			izq = true;
		}

		if (plano.x + plano.w > maxX) {
			der = true;
		}
		if (izq&&der) {
			plano.x = minX - (plano.w - (maxX - minX)) / 2;
			Centro.x = plano.x + plano.w / 2;
		}
		else {
			if (izq) {
				plano.x = minX;

			}
			if (der) {
				plano.x = maxX - plano.w;
			}
			Centro.x = plano.x + plano.w / 2;
		}
	}
	if (BloquearEjeY) {
		plano.y = minY - (plano.h - (maxY - minY)) / 2;
		Centro.y = plano.y + plano.h / 2;

	}
	else {
		bool top = false, bot = false;
		if (plano.y < minY) {
			top = true;
		}

		if (plano.y + plano.h > maxY) {
			bot = true;
		}
		if (top&&bot) {
			plano.y = minY - (plano.h - (maxY - minY)) / 2;
			Centro.y = plano.y + plano.h / 2;
		}
		else {
			if (top) {
				plano.y = minY;

			}
			if (bot) {
				plano.y = maxY - plano.h;
			}
			Centro.y = plano.y + plano.h / 2;
		}
	}

	switch (CameraState_)
	{
	case Camara::NORMAL:
		break;
	case Camara::SACUDIDA:
		plano.x += rand() % fuerzaTerremoto - fuerzaTerremoto/2;
		plano.y += rand() % fuerzaTerremoto - fuerzaTerremoto/2;
		break;
	default:
		break;
	}
	ultimoPlano = plano;
}

SDL_Rect Camara::getPlano()
{
	return plano;
}

void Camara::setLimite(SDL_Rect const &  area)
{
	if (plano.w > area.w)
		BloquearEjeX = true;
	else 
		BloquearEjeX = false;

	if (plano.h > area.h)
		BloquearEjeY = true;
	else
		BloquearEjeY = false;

	minX = area.x; minY = area.y; maxX = area.x + area.w; maxY = area.y + area.h;
}

SDL_Point Camara::getPosRelativa(SDL_Rect rec) {
	return{rec.x - plano.x + rec.w/2,rec.y-plano.y + rec.h / 2 };

}
SDL_Rect Camara::getRecRelativa(SDL_Rect rec) {
	rec.x -= plano.x;
	rec.y -= plano.y;
	return rec;
}
Uint32 restart(Uint32 interval, void* Param) {
	static_cast<Camara*>(Param)->restaurarCamara();
	return 1;
}
void Camara::sacudirCamara(Uint32 ms, Uint16 intensidad)
{
	fuerzaTerremoto = intensidad;
	CameraState_ = SACUDIDA;
	SDL_RemoveTimer(TemporazidorEfecto);
	TemporazidorEfecto = SDL_AddTimer(ms, restart, this);

}

