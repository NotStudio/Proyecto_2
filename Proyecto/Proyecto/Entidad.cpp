#include "Entidad.h"
#include "checkML.h"

Entidad::Entidad(Juego* punteroJuego, SDL_Rect spritePar, string objectId) : pJuego(punteroJuego)
{
	id = objectId;
	//Inicializacion de la animacion.
	animaciones = pJuego->getAnimaciones(id);
	currentAnim = animaciones[0];
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
	for (size_t i = 0; i < animaciones.size(); i++)
	{
		delete animaciones[i];
		animaciones[i] = nullptr;
	}
}


void Entidad::draw() {
	//Dibujamos el objeto.
	currentAnim->textura->draw(pJuego->getRender(), *getRect(), currentAnim->currentRect(),pJuego->getCamera(),(estadoEntidad.mirando==NorteOeste|| estadoEntidad.mirando == Oeste|| estadoEntidad.mirando == SurOeste));
	
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
