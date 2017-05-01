#include "HUDinventory.h"



HUDinventory::HUDinventory(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim) : pjuego(punteroJuego)
{

	id = objectId;
	anim = objectAnim;
	animacion.loadTextura(pjuego->getTextura(id, anim));
	
	
	sprite = new SDL_Rect(spritePar);
}


HUDinventory::~HUDinventory()
{
	delete sprite;
	sprite = nullptr;
}

void HUDinventory::draw(){


	
	animacion.textura = pjuego->getTextura(id, anim);
	animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.currentRect(), 0.0); 
	
	
	 
	std::map<std::string, int> mymap = pjuego->getInventory()->getMap();
	
	int i = 0;
	//Recorrer el map del inventario e ir dibujando los objetos.
	for (std::map<std::string, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		
		switch (i){
		case (0):
			animacion.textura = pjuego->getTextura(it->first, anim);
			animacion.textura->draw(pjuego->getRender(), SDL_Rect{ 180, 510, 60, 60 }, animacion.currentRect(), 0.0);
			break;
		case (1) :
			animacion.textura = pjuego->getTextura(it->first, anim);
			animacion.textura->draw(pjuego->getRender(), SDL_Rect{ 250, 510, 60, 60 }, animacion.currentRect(), 0.0);
			break;
		case (2) :
			animacion.textura = pjuego->getTextura(it->first, anim);
			animacion.textura->draw(pjuego->getRender(), { 310, 510, 60, 60 }, animacion.currentRect(), 0.0);
			break;
		case (3) :
			animacion.textura = pjuego->getTextura(it->first, anim);
			animacion.textura->draw(pjuego->getRender(), SDL_Rect{ 380, 510, 60, 60 }, animacion.currentRect(), 0.0);
			break;
		}

		i++;
		
	}
	
}
