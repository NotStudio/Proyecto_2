#pragma once
#include "Tile.h"
#include "TileInfo.h"
#include <vector>
using namespace std;
class Puerta
{
public:
	Puerta(Direcciones D) {
		DirPuerta = D;
		TilesPuerta.reserve(2);
	};
	void meteTilePuerta(Tile* T_) {
		TilesPuerta.push_back(T_);
	};
	void abrirPuerta() {
		for (auto p : TilesPuerta)
			p->SetTile(S6);
	};
	void cerrarPuerta() {
		for (auto p : TilesPuerta)
			p->SetTile(ROC);
	};
	Direcciones GetDir() {
		return DirPuerta;
	};
private:
	Direcciones DirPuerta;
	vector<Tile*> TilesPuerta;
};

