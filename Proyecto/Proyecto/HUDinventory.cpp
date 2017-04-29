#include "HUDinventory.h"



HUDinventory::HUDinventory(Juego* punteroJuego, SDL_Rect spritePar, SDL_Rect objs, string objectId, string objectAnim) : pjuego(punteroJuego)
{

	id = objectId;
	anim = objectAnim;
	animacion.loadTextura(pjuego->getTextura(id, anim));
	animacion2.loadTextura(pjuego->getTextura("Carbono", anim));

	sprite = new SDL_Rect(spritePar);
	obj = new SDL_Rect(objs);
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
	
	
	//Recorrer el map del inventario e ir dibujando los objetos.
	for (std::map<std::string, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		animacion2.textura = pjuego->getTextura(it->first, anim);
		animacion2.textura->draw(pjuego->getRender(), *getRect2(), animacion.currentRect(), 0.0);
		//obj->x += 50;
	}
	
}
