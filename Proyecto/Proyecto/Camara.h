#ifndef CAMARA_H_
#define CAMARA_H_
#include<SDL.h>
#include<SDL_image.h>
class Camara
{
public:
	Camara(SDL_Rect * target, int w, int h);
	Camara();
	~Camara();
	void setTarget(SDL_Rect*);
	void update();
	SDL_Rect getPlano();
	SDL_Rect getTarget() { return *Apuntando; }
	SDL_Point getTargetCentro() { return SDL_Point{ Apuntando->x + Apuntando->w / 2,Apuntando->y + Apuntando->h / 2 }; }
	SDL_Point getCentro() { return Centro; }
	double getAngulo() { return anguloCamara; }
	void setAngulo(double a) { anguloCamara = a; }
private:
	SDL_Point Centro;
	SDL_Rect * Apuntando;
	SDL_Rect plano;
	SDL_Rect ultimoPlano;
	double anguloCamara;
};
#endif // !CAMARA_H_


