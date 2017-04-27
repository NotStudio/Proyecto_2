#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_
#include <map>
class Inventory
{
public:
	Inventory();
	~Inventory();

	void insertItem(std::string const & name, int quantity);
	void removeItem(std::string const & name, int quantity);
	bool findItem(std::string const & name);
	int getCantidad(std::string const & name) const;

private:

	std::map<std::string, int> inventory;
};
#endif 
