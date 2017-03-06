#include "Entidad.h"


Entidad::Entidad(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : pJuego(punteroJuego)
{
	id = objectId;
	//Inicializacion de la animacion.
	currentAnim.numFrames = 0;
	currentAnim.textura = pJuego->getTextura(id, "idle");
	currentAnim.rect = nullptr;
	//Asignacion de los parametros de posicion.
	pos.x = spritePar.x;
	pos.y = spritePar.y;
	vel.y = vel.x = 0;
	//Asignacion de los parametros del SDL_Rect sprite, propio de la clase.
	sprite = new SDL_Rect(spritePar);
	
	
	 
}


Entidad::~Entidad()
{
	//Destruir cosas de la Física
	pJuego->getWorld()->DestroyBody(body);
	delete shape;
	delete sprite;
	//pJuego = nullptr;
}


void Entidad::draw() {
	//Dibujamos el objeto.
	currentAnim.textura->draw(pJuego->getRender(), *getRect(), currentAnim.rect,pJuego->getCamera());
	
}

void Entidad::update(){
	//Asignar sprite a body para que se dibuje.
	pos = body->GetPosition();
	sprite->x = (int)pos.x; sprite->y = (int)pos.y;

	

}

b2Body* Entidad::getBody() {
	return body;
}
