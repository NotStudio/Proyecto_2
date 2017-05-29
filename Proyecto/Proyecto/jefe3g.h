#pragma once
#include "Enemigo.h"
#include "BalaHacha.h"
#include "BalaMultiple.h"
#include "Bala.h"
#include "Room.h"
#include "Sierra.h"


enum States{ IDLE, MOVIMIENTO, ATAQUE1, ATAQUE2, ATAQUE3 };
enum  Phases{ FASE1, FASE2 };// Fase 1: hace el Ataque1 y el Ataque2. Fase2: hace los tres ataques.

class jefe3g : public Enemigo
{
public:
	jefe3g(Juego* punteroJuego, int x, int y);
	~jefe3g();


	virtual void comportamiento();// como si fuese el update
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);

	void estar();
	void Movimiento();// Te persigue como los "imanes" pero más lento.
	void Ataque1();// Invoca sierras.
	void Ataque2();// Lanza un proyectil que rebota ciertas veces.
	void Ataque3();// Carga hacia un lado con la motosierra extendida.

	void changeState();
	void eliminaSierra();
	void disparo();

	int i = 0;
	States estado;
	States viejo;
	Phases fase;
	bool empezado = false;
	int contador;

	float jugx;
	float jugy;

	int conts = 3;
	int contr = 3;
	int ewwe = 0;
	//////////////////////////////////////////////////////

	vector<Objeto*> sierras;
	int t = 0;
};

