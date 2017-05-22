#ifndef CAMARA_H_
#define CAMARA_H_
#include<SDL.h>
#include<SDL_image.h>
#include"LTimer.h"
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
	void setLimite(SDL_Rect const &  area);
	SDL_Point getPosRelativa(SDL_Rect rec);
	SDL_Rect getRecRelativa(SDL_Rect rec);
	void sacudirCamara(Uint32 ms);
	// parar de mover la camara
	void restaurarCamara() {
		CameraState_ = NORMAL;
	};
private:
	enum CAMERASTATE
	{
		NORMAL, SACUDIDA
	}CameraState_;
	static Uint32 restart(Uint32 interval, void* Param) {
		(CAMERASTATE&)Param = NORMAL;
		return 1;
	}
	SDL_TimerID TemporazidorEfecto;
	
	int minX, minY, maxX, maxY;
	SDL_Point Centro;
	SDL_Rect * Apuntando;
	SDL_Rect plano;
	SDL_Rect ultimoPlano;
	double anguloCamara;
};
#endif // !CAMARA_H_


