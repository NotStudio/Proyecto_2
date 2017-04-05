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
		return new Sierra(pj, x,y, 0);
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
Objeto* creaEntidad(Juego * pj, TMXReader::ObjectInfo * obj, int desvX, int desvY) {
	try
	{
		if (obj->getType() == "inanimado") {
			return creaInanimado(pj, obj->getName(), obj->getX() / 2 + desvX, obj->getY() / 2 + desvY, obj->getW() / 2, obj->getH() / 2);
		}
		else if (obj->getType() == "enemigo") {
			return creaEnemigo(pj, obj->getName(), obj->getX() / 2 + desvX, obj->getY() / 2 + desvY);
		}
		else {
			printf("this object has no type \n");
			return nullptr;
		}
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
	
}