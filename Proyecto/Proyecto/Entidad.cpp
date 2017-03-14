#include "Entidad.h"
#include "checkML.h"

Entidad::Entidad(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : pJuego(punteroJuego)
{
	id = objectId;
	//Inicializacion de la animacion.
	currentAnim.loadTextura(pJuego->getTextura(id, "idle"));
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
	delete sprite;
	pJuego->getWorld()->DestroyBody(body);
	//pJuego = nullptr;
}


void Entidad::draw() {
	//Dibujamos el objeto.
	currentAnim.textura->draw(pJuego->getRender(), *getRect(), currentAnim.currentRect(),pJuego->getCamera(),Dir.izq);
	
}

void Entidad::update(){
	//Asignar sprite a body para que se dibuje.
	pos = body->GetPosition();
	sprite->x = (int)pos.x; sprite->y = (int)pos.y;

	

}

//Retorna el cuerpo de la entidad
b2Body* Entidad::getBody() {
	return body;
}
