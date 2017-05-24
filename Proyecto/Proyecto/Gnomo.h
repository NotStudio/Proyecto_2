#pragma once
#include "Enemigo.h"
#include "LTimer.h"
#include "Sierra.h"
#include "BalaHacha.h"
#include "Room.h"

enum States{ IDLE, MOVIMIENTO , ATAQUE1, ATAQUE2 , ATAQUE3};
enum  Phase{ FASE1 , FASE2};// Fase 1: hace el Ataque1 y el Ataque2. Fase2: hace los tres ataques.
class Gnomo :
	public Enemigo
{
public:
	Gnomo(Juego* punteroJuego, int x, int y);
	virtual ~Gnomo();

	
	virtual void comportamiento();// como si fuese el update
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);

	void Idle();// Espera cierto tiempo
	void Movimiento();// Te persigue como los "imanes" pero más lento.
	void Ataque1();// Invoca sierras.
	void Ataque2();// Lanza un proyectil que rebota ciertas veces.
	void Ataque3();// Carga hacia un lado con la motosierra extendida.

	void changeState();
	void disparo(string tipo, SDL_Rect posicion, float dirx, float diry, float velocidad);
	void eliminaSierra();


	States estado;
	Phase fase;
	bool empezado = false;
	LTimer tiempo;
	int contador;

	vector<Objeto*> sierras;

	Sierra* s1;
	Sierra* s2;
	Sierra* s3;

	Room* r = static_cast<ZonaJuego*>(pJuego->getZona())->getRoomActual();

	float jugx;
	float jugy;

	int conts = 3;
	int contr = 3;

	vector<Objeto*>aux;
};

