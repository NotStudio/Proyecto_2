#pragma once
#include "Enemigo.h"
#include "LTimer.h"
enum Estados{Idle = 0,Ataque1 = 1,Ataque2 = 2,Ataque3 = 3,Ataque4 = 4}; // Idle espera entrre 0 y x segundos hasta que cambia a otro ataque(Dos de neumaticos y dos de coches)
enum  Fases{ Fase1= 1, Fase2 = 2,Fase3 = 3 };// Fases de la batalla por ejemplo en la fase dos debe aumentar todo y lanza un charco de aceite que te quita vida
class Jefe1 :
	public Enemigo
{
public:
	Jefe1(Juego* punteroJuego, int x, int y);
	~Jefe1();
	virtual void move();
	virtual void comportamiento();
	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2);
	void changeState();
	void Idle();
	void Ataque1();
	void Ataque2();
	void Ataque3();
	void Ataque4();

	void disparo(string tipo, SDL_Rect posicion, float dirx, float diry,float velocidad);//Llaman a esta función con un timer, para llamarla tienes que haber calculado rpeviamente la posicion y la velocidad
	void disparaAceite(float dirx, float diry);
	Estados estado;
	Fases fase;
	bool empezado = false;
	LTimer tiempo;
	int contador;
};

