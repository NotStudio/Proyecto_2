#ifndef JUEGO_H_
#define JUEGO_H_
#include <vector>
#include <string>
#include <Box2D\Box2D.h>
#include <unordered_map>
#include <float.h>
#include <stack>
#include "TexturasSDL.h"
#include "contactListener.h"
#include "Camara.h"
#include "HUDbase.h"
#include <SDL_mixer.h>

class ZonaJuego;
class EstadoJuego;
using namespace std;
class Juego
{
	
	int score;

	stack<EstadoJuego*> estados;
	Mix_Music *musicote;
	Mix_Chunk *aham;
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
	vector<string> nombreTexturas;
	vector<string> ubicacionTipografias;
	vector<string> ficherosHabitaciones;

	struct Ventana { //Struct que contiene el tama�o y el color de la ventana.
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
	struct _InfoTecla
	{
		bool presionada = false, mantenida = false;
	};
	_InfoTecla KEYS[322];

	unordered_map<string, unordered_map<string, TexturasSDL*>> mapTexturas;
	unordered_map<string, unordered_map<int, Fuente*>> fuentes;

	Camara *Camera;

	ZonaJuego* zona;

	Objeto* personaje;

	HUDbase* vidasHUD;
	
	

public:
	Juego(b2World * mundo);
	Juego();
	~Juego();

	
	struct Animacion
	{
		SDL_Rect rect;
		TexturasSDL* textura;
		int numFrames;
		int frameActual;
		Animacion() { rect = { 0,0,0,0 }; textura = nullptr; frameActual = 0; numFrames = 0; };
		void loadTextura(TexturasSDL*text, int nFrames = 1) {
			textura = text;
			numFrames = nFrames;
			rect = { 0,0,(int)textura->getAncho() / numFrames,(int)textura->getAlto() };
		}
		void setNumFrames(int nFrames) {
			numFrames = nFrames;
			rect.w = textura->getAncho() / numFrames;
		}
		SDL_Rect* currentRect(){
			return &rect;
		}
		void ActualizarFrame() {
			frameActual++;
			if (frameActual>=numFrames)
			{
					frameActual = 0;
			}
			rect.x = frameActual*rect.w;
		}
		Animacion operator=(Animacion const a){
			this->textura = a.textura;
			return *this;
		}
	};
	enum capaColisiones{
		ENEMIGO = 0x0001,
		AT_ENEMIGO = 0x0002,
		JUGADOR = 0x0004,
		AT_JUGADOR = 0x0008,
		ITEM = 0x0010,
		ESCENARIO = 0x0020,
		ESCENARIO_NOCOL = 0x0040

	};
	Fuente* getTipografia(const string & id, const int & tam=50) {
		try {
			return fuentes.at(id).at(tam);
		}
		catch (out_of_range) {
			try
			{
				string a = fuentes.at(id).at(fuentes.at(id).begin()->first)->fichero;
				fuentes.at(id);
				fuentes.at(id).emplace(make_pair(tam, new Fuente()));
				fuentes.at(id).at(tam)->loadFuente(a,tam);
				return fuentes.at(id).at(tam);
			}
			catch (out_of_range)
			{
				cout << "Error al cargar la tipografia, tome tipografia por defecto\n";
				return fuentes.at(fuentes.begin()->first).at(50);
			}
			
		}
	}
	string getRoom(){
		return ficherosHabitaciones[rand()%ficherosHabitaciones.size()];
	}
	vector<Animacion*>getAnimaciones(const string & entity) {
		vector<Animacion*> vec;
		try {
			int j = 0;
			for (auto i = mapTexturas.at(entity).begin(); i != mapTexturas.at(entity).end(); i++)
			{
				vec.push_back(new Animacion());
				vec[j]->loadTextura(i->second);
				j++;
			}
			return vec;
		}
		catch (out_of_range) {
			std::cout << "Error al cargar textura";
		}
	}
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

	void changeState(EstadoJuego* nwEstado);

	void pushState(EstadoJuego* nwEstado);

	void popState();

	EstadoJuego* topState();

	bool inputQuery(int numButton);

	bool teclaPulsada(int numButton);

	SDL_Rect getCameraRect() { return Camera->getPlano(); }
	Camara * getCamera() { return Camera; }
	
	b2World* getWorld();

	Objeto* getPlayer(){	return personaje ;
}
	TexturasSDL*getTilesheet(){	return mapTexturas.at("tilesheet").at("zon1");}

	ZonaJuego* getZona() {	return zona;}

	void setZona(ZonaJuego* nwZona);
};


#endif 