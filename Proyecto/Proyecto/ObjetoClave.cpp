#include "ObjetoClave.h"


ObjetoClave::ObjetoClave(Juego* punteroJuego, SDL_Rect spritePar) : Item(punteroJuego, spritePar, "TarjetaSD")
{

}


ObjetoClave::~ObjetoClave()
{
}

void ObjetoClave::onColisionEnter(Objeto * o, b2Body * b1, b2Body * b2)
{
	//NOTIFICAR DE QUE SE HA RECOGIDO UNA TARJETA
	destruido = true;
}
