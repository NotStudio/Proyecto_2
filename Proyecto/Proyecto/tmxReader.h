#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
using namespace rapidxml;
using namespace std;
int const tileW = 64;
struct ObjetoInfo
{
	string nombreEntidad;
	int x = 0;
	int y = 0;
	int adicional = 0;
	int h = -1;
	int w = -1;
	ObjetoInfo() {};
	ObjetoInfo(string nombre, int x, int y, int add) :nombreEntidad(nombre), x(x/2), y(y/2), adicional(add) {};
	ObjetoInfo(string nombre, int x, int y, int w, int h) :nombreEntidad(nombre), x(x/2), y(y/2), w(w/2), h(h/2) {};
};
struct Patron
{
	vector<ObjetoInfo> lineas;
	bool usado = false;
	void meter(ObjetoInfo o) {
		usado = true;
		lineas.push_back(o);
	}
};
struct Mapinfo {
	int ancho, alto;
	vector<string> Mapa;
	Patron patronesEnemigos[4];
	Patron patronesInanimados[4];
	void meterPatronEnemigos(string nombre, int x, int y, int NPatron = -1, int aditional = -1) {
		if (NPatron > 3 || NPatron < 0) {
			cout << "Numero de patrón Invalido, el NPatron de esta capa de Enemigos tiene que estar entre 0 y 3" << endl;
			return;
		}
		else {
			patronesEnemigos[NPatron].meter(ObjetoInfo(nombre, x, y, aditional));
		}
	};
	void meterPatronInanimados(string nombre, int x, int y, int w, int h, int NPatron = -1) {
		if (NPatron > 3 || NPatron < 0) {
			cout << "Numero de patrón Invalido, el NPatron de esta capa de inanimados tiene que estar entre 0 y 3" << endl;
			return;
		}
		else {
			patronesInanimados[NPatron].meter(ObjetoInfo(nombre, x, y, w, h));
		}
	};
	vector<ObjetoInfo> getPatronEnemigos(int n = 0) {
		if (n > 3 || n< 0) {
			if (n > 3)
				return getPatronEnemigos(n--);
			if (n < 0)
				return getPatronEnemigos(n++);
		}
		else if (!patronesEnemigos[n].usado) {
			if (!patronesEnemigos[0].usado)
			{
				return vector<ObjetoInfo>(1);
			}
			return patronesEnemigos[0].lineas;
		}
		else
		{
			return patronesEnemigos[n].lineas;
		}
	}
	vector<ObjetoInfo> getPatronInanimados(int n = 0) {
		if (n > 3 || n< 0) {
			if (n > 3)
				return getPatronInanimados(n--);
			if (n < 0)
				return getPatronInanimados(n++);
		}
		else if (!patronesInanimados[n].usado) {
			if (!patronesInanimados[0].usado)
			{
				return vector<ObjetoInfo>(1);
			}
			return patronesInanimados[0].lineas;
		}
		else
		{
			return patronesInanimados[n].lineas;
		}
	}
};

Mapinfo lector(string dir);
	


