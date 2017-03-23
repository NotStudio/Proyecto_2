#include "InanimadoInfo.h"
#include "EnemigoBomba.h"
#include "Sierra.h"
#include "Helice.h"
#include "Perseguidor.h"
#include <stdio.h>


Inanimado * creaInanimado(Juego * pj, string id, int x, int y, float escala ) {
	
	if (id == "tuberia" || id == "Tuberia")
	{
		return new Tuberia(pj, { x, y }, escala);
	}
	else if (id == "nave")
	{
		return new Nave(pj, { x, y }, escala);
	}
	else if (id == "chatarra")
	{
		return new Chatarra(pj, { x, y }, escala);
	}
	else if (id == "agujero")
	{
		return new Agujero(pj, { x, y }, escala);
	}
	else
	{
		throw exception("NO EXISTE DICHO OBJETO \n");
	}
}
Enemigo* creaEnemigo(Juego * pj, string id, int x, int y, int aditional){
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