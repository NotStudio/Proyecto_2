#include "factoriaEntidades.h"
#include "EnemigoBomba.h"
#include "Sierra.h"
#include "Helice.h"
#include "Perseguidor.h"
#include "Inanimado.h"
#include "MaquinaDePelotas.h"
#include "Jefe1.h"
#include "Dron.h"
#include "TrampaElectrica.h"
#include "Jefe2Bouncer.h"
#include "Gnomo.h"
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
	else if (id == "SelectorCambio" || id == "selectorcambio") {
		return new SelectorCambio(pj, x, y, w, h);
	}
	else if (id == "SelectorCrafteo" || id == "selectorcrafteo") {
		return new SelectorCrafteo(pj, x, y, w, h);
	}
	else if (id == "findezona" || id == "FinDeZona") {
		return new FinZona(pj, x, y, w, h);
	}
	else
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
	else if (id == "Jefe1" || id == "jefe1")
	{
		return new Jefe1(pj, x, y);
	}
	else if (id == "Jefe2" || id == "jefe2") {
		return new Jefe2Bouncer(pj, x, y, 1);
	}
	else if (id == "Gnomo" || id == "gnomo") {
		return new Gnomo(pj, x, y);
	}
	else if (id == "Tornillero" || id == "tornillero"){

		return new MaquinaDePelotas(pj, x, y);
	}
	else if (id == "TrampaElectrica" || id == "trampaElectrica") {
		return new TrampaElectrica(pj, x, y);
	}
	else if (id == "Dron" || id == "dron") {
		return new Dron(pj, x, y);
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