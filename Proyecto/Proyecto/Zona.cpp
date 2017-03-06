#include "Zona.h"


Zona::Zona()
{
	
}


Zona::~Zona()
{
}

bool Zona::nextLevel(){

	return	niveles.avanza();
}

bool Zona::previousLevel(){
	return niveles.retrocede();
}


Nivel* Zona::getCurrentLevel(){
	return niveles.getCurrent();
}