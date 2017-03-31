#include "factoriaEntidades.h"
#include "EnemigoBomba.h"
#include "Sierra.h"
#include "Helice.h"
#include "Perseguidor.h"
#include "Inanimado.h"
#include <stdio.h>


Objeto * creaInanimado(Juego * pj, string id, int x, int y, int w, int h,float escala ) {
	
	if (id == "tuberia" || id == "Tuberia")
	{
		return new Tuberia(pj, x,y,w,h);
	}
	else if (id == "nave")
	{
		return new Nave(pj, x, y, w, h);
	}
	else if (id == "chatarra")
	{
		return new Chatarra(pj, x, y, w, h);
	}
	else if (id == "agujero")
	{
		return new Agujero(pj, x, y, w, h);
	}
	else if (id == "SelectorZona" || id == "selectorzona") {
		return new SelectorZona(pj, x, y, w, h);
	}
	{
		throw exception("NO EXISTE DICHO OBJETO \n");
	}
}
Objeto* creaEnemigo(Juego * pj, string id, int x, int y, int aditional){
	if (id == "perseguidor" || id == "Perseguidor")
	{
		return new Perseguidor(pj, x,y);
	}
	else if (id == "Sierra"||id=="sierra")
	{
		return new Sierra(pj, x,y, aditional);
	}
	else if (id == "helice" || id == "Helice")
	{
		return new Helice(pj, x,y);
	}
	else if (id == "Bomba" || id == "bomba")
	{
		return new EnemigoBomba(pj, x, y );
	}
	else
	{
		throw exception("NO EXISTE DICHO ENEMIGO \n");
	}
}