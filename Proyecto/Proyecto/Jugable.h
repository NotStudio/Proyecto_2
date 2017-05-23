#ifndef JUGABLE_H_
#define JUGABLE_H_

#include "Personaje.h"
class Jugable :
	public Personaje
{
public:
	Jugable(Juego* punteroJuego, SDL_Rect spritePar,string objectId);
	virtual ~Jugable();

	void virtual update();

	Personaje::atributos* getStats() { return &stats; };
	virtual void onColisionEnter(Objeto* obj , b2Body* b1, b2Body* b2);
	void quitarInmunidad(){
		inmune = false;
		resetAlpha();
		
		
	}

	enum estado{JUGANDO, BASE};

	estado getEstado(){ return state; }

	void cambiaEstado(estado s) {

		state = s;
	}

	void setPos(float32 x, float32 y) {
		body->SetTransform(b2Vec2{ x / PPM, y / PPM }, 0);
		
	}
	
	void velocidad(){
		stats.velMov *= 4;
		ralentizado = false;
		
	}

	void stop();

protected:

	//Booleanas para el control del movimiento, utilizadas en el movControl;
	//Mueve.
	void move();
	//Recoge el input de la clase Juego.
	void movControl();
	//Controla que pare suave.
	void afinarMov(int const & vel, int const & lim,Direccion const &);
	//Acceso inventario
	//void inventario();
	bool lel = true;
	bool inmune = false;
	bool ralentizado = false;
	SDL_TimerID timerInmune;
	SDL_TimerID timerRalentizado;
	estado state;
private:
	int alphaFactor;
	int alphaMultiplicador;
	void feedbackInvulnerable();
	void resetAlpha();
	
};
#endif
