#ifndef CAMBIO_H_
#define CAMBIO_H_
#include "EstadoPG.h"
#include "Boton.h"
#include "Room.h"
#include <vector>



class Cambio : public  EstadoPG
{
public:
	Cambio(Juego * juego,int actual,int Personajes);
	~Cambio();
	int activo = 0;
	int frame;


private:
	int personajes;
	Room* pR;
	unordered_map<string, Juego::Animacion*> mapaAnims;
	vector<Juego::Animacion*> animaciones;
	Boton*boton;
	TextoSDL PJSelected;

	static void resume(Juego * jg);
	static void returnMenu(Juego * jg);

	// Estos métodos no irían en EstadoPG, ya que menu y pausa los usan iguales
	virtual void update();
	virtual void draw();
	void activar(Juego * jg){
		jg->setActivo(activo);
	}
	void cambiaMapa(int i);
	void elijeTexto(int i);
};
#endif