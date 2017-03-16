#ifndef INANIMADOINFO_H_
#define INANIMADOINFO_H_
#include <SDL.h>
#include "TileInfo.h"
#include "Inanimado.h"
Inanimado * creaInanimado(Juego * pj, string id, int x, int y, float escala = 1) {
	if (id=="tuberia"||id=="Tuberia")
	{
		return new Tuberia(pj, { x,y }, escala);
	}
	else if (id == "nave")
	{
		return new Nave(pj, { x,y }, escala);
	}
	else if (id=="chatarra")
	{
		return new Chatarra(pj, { x,y }, escala);
	}
	else if (id == "agujero")
	{
		return new Agujero(pj, { x,y }, escala);
	}
	else
	{
		throw exception("becario");
	}
}
#endif // !INANIMADOINFO_H_
