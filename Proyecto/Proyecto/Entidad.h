#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include <Box2D\Box2D.h>
#include <SDL.h>
#include "Objeto.h"
#include "Juego.h"

class Entidad :	public Objeto
{
protected:
	Juego* pJuego; //Puntero al juego
	b2Vec2 pos; //Posicion del objeto.
	b2Vec2 vel; //Velocidad del objeto.
	SDL_Rect * sprite;//Posicion (que es la misma de arriba) y tamaño del objeto.
	//Atributos de Box2D
	b2Shape* shape;
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fDef;
	//Struct de animacion.
	unordered_map<string,Juego::Animacion*> animaciones;
	Juego::Animacion* currentAnim;
	//Nombre entidad
	string id;
	//Gestor de animaciones.
	 //virtual void updateAnim();
	//para ver si ha sido destruido
	bool destruido = false;
	enum Direccion
	{
		Norte, Este, Sur, Oeste, NorteEste,NorteOeste,SurEste,SurOeste,SinDir
	};
	enum EstadoAnimacion
	{
		Idle, Walk, Ataque,NoAnim
	};
	struct EntidadInfo
	{
		Direccion mirando=Este;
		EstadoAnimacion animacionActual = Idle;
	}estadoEntidad;
public:
	Entidad(Juego* punteroJuego, SDL_Rect spritePar , string objectId);

	virtual bool getdestruido() { return destruido; };

	virtual ~Entidad();

	virtual void draw();

	virtual void update();

	b2Body* getBody();

	std::string getId() { return id; };
	float getX(){
		return pos.x * PPM;

	}
	float getY(){
		return pos.y * PPM;
	}
	virtual SDL_Rect * getRect() {
		return sprite;
	}


	

	
	

};
#endif // !ENTIDAD_H_

