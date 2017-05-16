#include "HUD.h"
#include "Jugable.h"


HUD::HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim) : pjuego(punteroJuego), kruk(pjuego, "TEXTOPRUEBA", 30)
{
	id = objectId;
	anim = objectAnim;// Para las vidas esto tiene que ser: "Cuatro", solo al principio
	animacion.loadTextura(pjuego->getTextura(id, anim));
	// No se si el nombre este tiene que tener longitud 4, 
	//porque en juego initMedia() se hace substr de una cadena de 4 caracteres.
	sprite = new SDL_Rect(spritePar);
}
void HUD::updateHUD(){
	Jugable * jugador;
	jugador = static_cast<Jugable *> (pjuego->getActiveCharacter());
	switch (jugador->getVida()){
	case 1:
		vida.loadImage("Battery1");
		break;
	case 2:
		vida.loadImage("Battery2");
		break;
	case 3:
		vida.loadImage("Battery3");
		break;
	case 4:
		vida.loadImage("Battery4");
		break;
	}
	//FALTA HACER QUE SE ACTUALICE EL HUD
}


HUD::~HUD()
{

	delete sprite;
	pjuego = nullptr;
}

void HUD::draw(){

	int n;

/*	n = static_cast<Jugable*>(pjuego->getPlayer())->getStats()->vida;
	

	switch (n){
		
	case 4:// Tengo que ver como hacer para cuando se suman vidas que se vuelva a poner "Cuatro"
		animacion.textura = pjuego->getTextura("Battery4", anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.currentRect(),90);
		break;
	case 3:
		id = "Battery3";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.currentRect(),90);
		break;
	case 2:
		id = "Battery2";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.currentRect(),90);
		break;
	case 1:
		id = "Battery1";
		animacion.textura = pjuego->getTextura(id, anim);
		animacion.textura->draw(pjuego->getRender(), *getRect(), animacion.currentRect(), 90);
		break;
	}*/
	
}
