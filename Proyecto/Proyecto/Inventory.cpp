#include "Inventory.h"


// En la colisión con un objeto (este tiene que tener un atributo string que le identifique y otro para la cantidad)
//si es del tipo de objeto para el crafteo se inserta ese objeto con el identificador y la cantidad correspondiente.
// ***La cantidad en cada objeto se podría hacer aleatoria***
Inventory::Inventory()
{
	//insertItem("Chatarra", 2);
	//insertItem("BalaN", 1);

}


Inventory::~Inventory()
{
	
}

std::map<std::string, int> Inventory::getMap(){

	return inventory;
}

bool Inventory::findItem(std::string const & name)
{
	//Standard containers can only throw an out-of-range exception on access, they do not throw exceptions on other operations.
	try {
		inventory.at(name);
		return true;
	}
	catch (std::out_of_range & e) {
		return false;
	}


}

void Inventory::insertItem(std::string const & name, int quantity){

	if(!findItem(name))
		inventory.insert(std::pair<std::string, int>(name, quantity));
	else 
		inventory.at(name) += quantity;
}



void Inventory::removeItem(std::string const & name, int cantidad)
{
	if (findItem(name)) inventory.at(name) -= cantidad;

	if (inventory.at(name) <= 0)
		inventory.erase(name);
}



int Inventory::getCantidad(std::string const & name) const {
	return inventory.at(name);
}
