#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_
#include <map>
#include "TexturasSDL.h"

class Inventory
{
public:
	Inventory(int espacio, Fuente* tipografia, SDL_Renderer* render);
	virtual ~Inventory();

	void insertItem(std::string const & name, int quantity);
	void removeItem(std::string const & name, int quantity);
	bool findItem(std::string const & name);
	int getCantidad(std::string const & name) const;
	std::map<std::string, int> getMap();



private:

	int espacio_;
	TextoSDL texto;
	SDL_Renderer* render_;
	std::map<std::string, int> inventory;
};
#endif 
