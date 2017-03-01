#pragma once
#include "doubleLinkedList.h"
#include "Nivel.h"
class Zona
{
public:
	Zona();
	~Zona();

	Nivel* getCurrentLevel();

	bool nextLevel();

	bool previousLevel();

private:

	DoubleLinkedList<Nivel*> niveles;
	

};

