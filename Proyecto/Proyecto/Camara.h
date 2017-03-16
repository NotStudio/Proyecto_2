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
	bool Dentro(SDL_Rect * const rect) {
		return (rect->x > plano.x + plano.w || rect->x + rect->w < plano.x || rect->y > plano.y + plano.h || rect->y + rect->h < plano.y);
	}
	void setLimite(SDL_Rect & const area);
	SDL_Point getPosRelativa(SDL_Rect rec);
private:
	/*
	struct Limit
	{
		Limit() { topLeft = topRight = bottomLeft = bottomRight = 0; };
		void set(SDL_Rect r) { topLeft = r.x; topRight = r.x + r.w; topLeft = r.y; bottomRight = r.y + r.h; };
		void ser(int x, int y, int z, int d){ topLeft = x, topRight = z,  }
		int topLeft, topRight, bottomLeft, bottomRight;
	};
	*/
	int minX, minY, maxX, maxY;
	SDL_Point Centro;
	SDL_Rect * Apuntando;
	SDL_Rect plano;
	SDL_Rect ultimoPlano;
	double anguloCamara;
};
#endif // !CAMARA_H_


