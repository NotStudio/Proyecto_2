#ifndef ROOM_H_
#define ROOM_H_
#include "Juego.h"
#include "Tile.h"
#include "TileInfo.h"
#include "Bala.h"

class Room
{
private:
	SDL_Rect * area;
	//la zona de la room
	Juego * pJuego;
	Tilesheet * textTiles;
	//el vector de los tiles
	Puerta puertas[4];
	int numPuertas=0;
	vector<vector<Tile*>> Tiles;
	vector<vector<bool>> ocupados;
	void moverMapa(int desplazamientoX, int desplazamientoY);
	
	void getTileOcupable(SDL_Rect &);
	//Vector de enemigos.
	vector<Objeto*> enemigos;
	//Vector de objetos inanimados.
	vector<Objeto*> objetos;
	//Dificultad.(int, struct)
	vector<Objeto*> extras;//Balas
	void ColocarHabitacion(vector<Room*> *habitaciones);
	void marcarOcupados(vector<SDL_Point>const );
	vector<vector<bool>> getOcupados() { 
		return ocupados;
	}
	




public:
	int getNumPuertas() {
		return numPuertas;
	}
	void setPuertas(int dicc);
	void nuevaBala(Bala*bala){
		extras.push_back(bala);
	}
	bool dentroRoom(SDL_Point* box) {
		return !(area->x > box->x || area->x + area->w < box->x || area->y > box->y || area->y + area->h < box->y);
	}
	bool dentroRoom(SDL_Rect box) {
		return !(area->x >= box.x + box.w || area->x + area->w <= box.x || area->y >= box.y + box.h || area->y + area->h <= box.y);
	}
	//para saber las puertas donde estan
	SDL_Rect getArea() {
		return *area;
	}
	void update();
	//Room();
	Room(Juego *, vector<Room*>*);
	~Room();
	void render();
	int encontrarPosicionTiled(int & const x, int & const y);
	vector<SDL_Point> TilesOcupados(SDL_Rect const recto, bool & a );
	void SetRoomFichero(string Dir, vector<Room*> * Habitaciones);
	void stop();
	void meterInanimados(string const dir);
private:
	struct keks
	{
		Room* hab;
		vector<std::pair<SDL_Rect,Direcciones>> posibles;
		keks(Room*h, SDL_Rect r, Direcciones d) {
			hab = h;
			posibles.push_back({ r,d });
		}
	};
	SDL_Point lazyFoo(vector<keks> rooms, Room*&k, Direcciones & D) {
		srand(SDL_GetTicks());
		int a = rand() % rooms.size();
		int b = rand() % rooms[a].posibles.size();
		k = rooms[a].hab;
		D = rooms[a].posibles[b].second;
		cout << "Se conecta la " << a << " la " << rooms.size() ;
		if (D == Norte){
			cout << " Por Norte ";
		}if (D == Sur){
			cout << " Por Sur ";
		}
		cout << "\n";
		return{ rooms[a].posibles[b].first.x,rooms[a].posibles[b].first.y };
	}
	bool solapa(SDL_Rect const & a, SDL_Rect const & b) {
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;
		leftA = a.x; rightA = a.x + a.w; topA = a.y; bottomA = a.y + a.h;
		leftB = b.x; rightB = b.x + b.w; topB = b.y; bottomB = b.y + b.h;
		if (bottomA <= topB) { return false; } if (topA >= bottomB) { return false; } if (rightA <= leftB) { return false; } if (leftA >= rightB) { return false; }
		return true;
	}


	vector<keks> solapamientoHabitaciones(vector<Room*> * Habitaciones, SDL_Rect & zona) {
		vector<keks> posiblis;
		int cont = 0;
		for (size_t i = 0; i < Habitaciones->size(); i++)
		{
			int okX = Habitaciones->at(i)->getArea().x, okY = Habitaciones->at(i)->getArea().y;
			int okW = Habitaciones->at(i)->getArea().w, okH = Habitaciones->at(i)->getArea().h;
			bool ayy = false;

			zona.x = okX + (okW - zona.w) / 2;
			zona.y = okY - zona.h;
			bool valido = true;
			for (size_t j = 0; j < Habitaciones->size(); j++)
			{
				if (solapa(zona, Habitaciones->at(j)->getArea())) valido = false;
			}
			if (valido && !ayy) { ayy = true; posiblis.push_back(keks(Habitaciones->at(i), zona,Direcciones::Norte)); }
			else if (valido &&ayy)posiblis[cont].posibles.push_back(make_pair(zona,Direcciones::Norte));
			valido = true;
			zona.x = okX + (okW - zona.w) / 2;
			zona.y = okY + okH;
			for (size_t j = 0; j < Habitaciones->size(); j++)
			{
				if (solapa(zona, Habitaciones->at(j)->getArea())) valido = false;
			}
			if (valido && !ayy) { ayy = true; posiblis.push_back(keks(Habitaciones->at(i), zona,Direcciones::Sur)); }
			else if (valido&&ayy)posiblis[cont].posibles.push_back(make_pair(zona, Direcciones::Sur));

			zona.y = okY + (okH - zona.h) / 2;
			zona.x = okX + okW;
			valido = true;

			for (size_t j = 0; j < Habitaciones->size(); j++)
			{
				if (solapa(zona, Habitaciones->at(j)->getArea())) valido = false;
			}

			if (valido && !ayy) { ayy = true; posiblis.push_back(keks(Habitaciones->at(i), zona,Direcciones::Este)); }
			else if (valido&&ayy)posiblis[cont].posibles.push_back(make_pair(zona, Direcciones::Este));
			zona.x = okX - zona.w;
			valido = true;

			for (size_t j = 0; j < Habitaciones->size(); j++)
			{
				if (solapa(zona, Habitaciones->at(j)->getArea())) valido = false;
			}

			if (valido && !ayy) { ayy = true; posiblis.push_back(keks(Habitaciones->at(i), zona,Direcciones::Oeste)); }
			else if (valido&&ayy)posiblis[cont].posibles.push_back(make_pair(zona, Direcciones::Oeste));

			if (ayy) cont++;
		}
		return posiblis;
	}
}; // !1
#endif // !ROOM_H_