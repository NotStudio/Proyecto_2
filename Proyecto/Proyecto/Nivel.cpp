#include "Nivel.h"
#include <stdlib.h>
#include<time.h>
struct Cosa
{
	int dato;
	bool pN=false, pS=false, pE=false, pO=false;
	Cosa * Norte=nullptr;
	Cosa * Sur=nullptr;
	Cosa * Este=nullptr;
	Cosa * Oeste=nullptr;
};

void Gen(Cosa* cosica, int prob, int numR, vector<Cosa*> & vec,int current) {
	if (cosica->pN) {
		cosica->Norte = new Cosa;
		current++;
		cosica->Norte->dato = current;
	}
}

void Nivel::genNivel()
{
	srand(time(NULL));
	int kek=75;
	vector<Cosa*> lista;
	lista.push_back(new Cosa);
	lista[0]->dato = 1;
	lista[0]->pN = (rand() % 100 >kek);
	if (lista[0]->pN)kek -= 10;
	lista[0]->pS = (rand() % 100 >kek);
	if (lista[0]->pN)kek -= 10;
	lista[0]->pE = (rand() % 100 >kek);
	if (lista[0]->pN)kek -= 10;
	lista[0]->pO = (rand() % 100 >kek);
	if (lista[0]->pN)kek -= 10;
	Gen(lista[0], kek, 8, lista, 1);

}
Nivel::Nivel(Juego * j,int numRooms)
{
	pJuego = j;
	nRooms = numRooms;
}

Nivel::Nivel()
{
	pJuego = nullptr;
}


Nivel::~Nivel()
{
}
