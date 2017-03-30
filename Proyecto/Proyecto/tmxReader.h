#pragma once
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
struct ObjetoInfo
{
	string nombreEntidad;
	string tipo;
	int x;
	int y;
	int h;
	int w;
	ObjetoInfo(string nombre,string type, int x, int y, int add);
	ObjetoInfo(string nombre, string type, int x, int y, int w, int h);
	ObjetoInfo() :nombreEntidad(" "), x(0), y(0), h(0),w(0){};
};
struct Patron
{
	vector<ObjetoInfo> lineas;
	bool usado;
	void meter(ObjetoInfo o){
		lineas.push_back(o);
	}
};
struct Mapinfo {
	int ancho, alto;
	vector<vector<int>> Mapa;
	vector<Patron> Patrones;
};

Mapinfo lector();
	


