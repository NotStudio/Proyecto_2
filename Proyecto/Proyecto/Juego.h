#ifndef JUEGO_H_
#define JUEGO_H_
#include <vector>
#include <string>
#include <Box2D\Box2D.h>
#include <unordered_map>
#include <float.h>
#include <time.h>
#include <stack>
#include "TexturasSDL.h"
#include "contactListener.h"
#include "Camara.h"
#include "HUDbase.h"
#include <SDL_mixer.h>
#include "RoomInfo.h"
#include "MapData.h"
#include "Inventory.h"

class Zona;
class EstadoJuego;
using namespace std;
class Juego
{
	
	float FPSCAP = 1 / 60.0F;
	int score;
	int activo = 0;
	int personajes = 0;
	float accumulator = 0;
	stack<EstadoJuego*> estados;

	bool mostrar = false;


	
	void initMedia();
	
	void initHabitaciones();

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
	static Uint32 timerMus(Uint32 interval, void*Param){
		static_cast<Juego*>(Param)->meterMusica();
		return 0;
	}
	SDL_Window* pWindow;

	SDL_Renderer* pRenderer;
	vector<string> nombreTexturas;
	vector<string> ubicacionTipografias;
	
	vector<string> UbicacionSonidos;
	

	
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
	unordered_map<string, Mix_Music*> Musica;
	unordered_map<string, Mix_Chunk*> Efectos;
	
	unordered_map<string, TMXReader::MapData*> Habitaciones;
	unordered_map<string, TMXReader::MapData*> HabitacionesIni;
	unordered_map<string, TMXReader::MapData*> HabitacionesBoss;
	TMXReader::MapData* Base;

	Mix_Music * MusicaActual;
	Mix_Music * MusicaSig;
	Camara *Camera;
	
	Zona* zona;

	Objeto* personaje;

	Inventory* inventario;

	Inventory* baul;

	SDL_TimerID timerCambio;
public:
	Juego(b2World * mundo);
	Juego();
	~Juego();

	struct Ventana { //Struct que contiene el tamaño y el color de la ventana.
		int ancho;
		int alto;
		SDL_Color color;
	} window;
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

	void NewPersonaje(){
		personajes++;
	}

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
	
	Mix_Music* cargarMusica(string id) {
		try
		{
			return Musica.at(id);
		}
		catch (out_of_range)
		{
			printf("No se ha encontrado la cancion, Cancion por Defecto\n");
			return Musica.at(Musica.begin()->first);
		}
	}
	Mix_Chunk* cargarEfecto(string id) {
		try
		{
			return Efectos.at(id);
		}
		catch (out_of_range)
		{
			printf("No se ha encontrado el efecto, Cancion por Defecto\n");
			return Efectos.at(Efectos.begin()->first);
		}
	}
	
	void setVolumenMusica(int newVol) {
		newVol=(newVol<125 ) ? newVol:125 ;
		Mix_VolumeMusic(newVol);
	}
	void reproducirMusica(int loops= -1) {
		Mix_PlayMusic(MusicaActual, loops);
	}
	void pararMusica(){
		Mix_PauseMusic();
	}
	//El id es la cancion que quieres meter;
	void cambiarMusica(string id);
	void meterMusica() {
		MusicaActual = MusicaSig;
		Mix_FadeInMusic(MusicaActual, -1, 2000);
	}
	void quitarMusica(){
		Mix_FadeOutMusic(1000);
	}
	void reproducirEfecto(string id) {
		Mix_PlayChannel(-1,cargarEfecto(id),0);
	}


	TMXReader::MapData* getRoom(){
		srand(SDL_GetTicks());
		unordered_map<string, TMXReader::MapData*>::iterator it = Habitaciones.begin();
		size_t lim = rand() % Habitaciones.size();
		for (size_t i = 0; i < lim; i++)
		{
			it++;
		}
		return Habitaciones.at(it->first);
	}
	TMXReader::MapData* getIniRoom() {
		srand(SDL_GetTicks());
		unordered_map<string, TMXReader::MapData*>::iterator it = HabitacionesIni.begin();
		size_t lim = rand() % HabitacionesIni.size();
		for (size_t i = 0; i < lim; i++)
		{
			it++;
		}
		return HabitacionesIni.at(it->first);
	}
	TMXReader::MapData* getBossRoom() {
		srand(SDL_GetTicks());
		unordered_map<string, TMXReader::MapData*>::iterator it = HabitacionesBoss.begin();
		size_t lim = rand() % HabitacionesBoss.size();
		for (size_t i = 0; i < lim; i++)
		{
			it++;
		}
		return HabitacionesBoss.at(it->first);
	}

	TMXReader::MapData* getBaseRoom() {
		return Base;
	}

	unordered_map<string, Animacion*>getAnimaciones(const string & entity){
		unordered_map<string, Animacion*> an;
		try {
			for (unordered_map<string,TexturasSDL*>::iterator it = mapTexturas.at(entity).begin(); it != mapTexturas.at(entity).end(); it++)
			{
				an.emplace(make_pair(it->first, new Animacion()));
				an.at(it->first)->loadTextura(it->second);
			}
			return an;
		}
		catch (out_of_range) {
			std::cout << "Error al cargar textura";
		}
	}
	TexturasSDL* getTextura(const string &entity, const string &anim);

	void setPlayer(Objeto* pj) { personaje = pj; };

	void setCamera(Camara* c) { Camera = c; };

	Ventana getWindow() { return window; };

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

	void popStateandCamera(); //Hace lo mismo que el otro pop pero cambia la camara

	EstadoJuego* topState();

	bool inputQuery(int numButton);

	bool teclaPulsada(int numButton);

	SDL_Rect getCameraRect() { return Camera->getPlano(); }
	Camara * getCamera() { return Camera; }
	
	b2World* getWorld();

	Objeto* getPlayer(){	return personaje ;
}
	TexturasSDL*getTilesheet(Zona * z);

	Zona* getZona() {	return zona;}

	void setZona(std::string zonaNombre);

	void freeEstadoss();
	void setActivo(int n){
		activo = n;
	}
	int getActivo(){
		return activo;
	}
	int getPersonajes(){
		return personajes;
	}
	void setGameOver();

	void reiniciar();

	void changeInventory(){// cambia el estado del inventario
	
		mostrar = !mostrar;
	};

	bool getMostrar(){

		return mostrar;
	}

	Inventory* getInventory(){

		return inventario;
	}

	void setInventory(Inventory* i){
		inventario = i; //establece el inventario creado en Play.
	}

	Inventory* getBaul(){
	
		return baul;
	}

	void setBaul(Inventory* i){
		baul = i; //establece el baul creado en Play.
	}
};


#endif 