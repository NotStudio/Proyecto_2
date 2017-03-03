#ifndef JUEGO_H_
#define JUEGO_H_
#include <vector>
#include <string>
#include <Box2D\Box2D.h>
#include "TexturasSDL.h"
#include <float.h>
#include <stack>
#include <unordered_map>
#include "contactListener.h"
#include "Room.h"
#include "Camara.h"

class EstadoJuego;

using namespace std;


class Juego
{
	
	int score;

	stack<EstadoJuego*> estados;

	void initMedia();

	void freeMedia();

	bool initSDL();

	void closeSDL();

	void run();

	SDL_Rect r;
	SDL_Rect r2;
	b2Vec2 pos;
	b2World * world;
	contactListener listener;
	b2Body * tostadora;
	b2Body * gato;
	b2Body * wall;
	std::vector<Objeto*> objetos;

	SDL_Rect recta;

	SDL_Window* pWindow;

	SDL_Renderer* pRenderer;

	vector<TexturasSDL*> texturas;

	vector<string> nombreTexturas;

	struct Ventana { //Struct que contiene el tamaño y el color de la ventana.
		int ancho;
		int alto;
		SDL_Color color;
	} window;

	bool error, gameOver, exit;

	struct Mouse {
		int x;
		int y;

	}mousePos;
	
	SDL_Rect fondoRect;

	char moveC;

	bool KEYS[322];

	unordered_map<string, unordered_map<string, TexturasSDL*>> mapTexturas;
	Camara Camera;
	

	

public:
	Juego(b2World * mundo);
	~Juego();


	struct Animacion
	{
		SDL_Rect* rect;
		TexturasSDL* textura;
		int numFrames;
	};

	TexturasSDL* getTextura(const string &entity, const string &anim);

	SDL_Renderer* getRender() const;

	void getMousePos(int &mpx, int &mpy) const;

	bool getError();

	void salir();

	bool handle_event();

	static const Uint32  MSxUpdate = 17;

	Uint32 lastUpdate;

	void update();

	void draw();

	bool inputQuery(int numButton);

	SDL_Rect getCameraRect() { return Camera.getPlano(); }
	Camara getCamera() { return Camera; }

	b2World* getWorld();
	//Personaje activo queda ajustarlo para que pueda cambiar y no sea siempre el primero de la lista
	//pero para hacer el apanyo nos sirvfe de momento
	Objeto*personajeActivo(){
		return objetos[0];
	}

};


#endif 