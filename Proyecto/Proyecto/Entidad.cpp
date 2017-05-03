#include "Entidad.h"
#include "checkML.h"
#include <math.h>

Entidad::Entidad(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : pJuego(punteroJuego) 
{
	id = objectId;
	//Inicializacion de la animacion.
	animaciones = pJuego->getAnimaciones(id);
	currentAnim = animaciones.at(animaciones.begin()->first);
	//Asignacion de los parametros de posicion.
	pos.x = spritePar.x / PPM;
	pos.y = spritePar.y / PPM;
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
	for (unordered_map<string,Juego::Animacion*>::iterator it = animaciones.begin(); it != animaciones.end(); it++)
	{
		delete animaciones.at(it->first);
		animaciones.at(it->first) = nullptr;
	}
	
	delete shape;
	shape = nullptr;
}


void Entidad::draw() {
	//Dibujamos el objeto.
	currentAnim->textura->draw(pJuego->getRender(), *getRect(), currentAnim->currentRect(),pJuego->getCamera(),(estadoEntidad.mirando==NorteOeste|| estadoEntidad.mirando == Oeste|| estadoEntidad.mirando == SurOeste));
	
}

void Entidad::update(){
	//Asignar sprite a body para que se dibuje.
	pos = body->GetPosition();
	sprite->x = (int)round(pos.x * PPM); sprite->y = (int)round(pos.y * PPM);

	

}

//Retorna el cuerpo de la entidad
b2Body* Entidad::getBody() {
	return body;
}
