#include "ObjetoClave.h"


ObjetoClave::ObjetoClave(Juego* punteroJuego, SDL_Rect spritePar) : Item(punteroJuego, spritePar, "TarjetaSD")
{

}


ObjetoClave::~ObjetoClave()
{
}

void ObjetoClave::onColisionEnter(Objeto * o, b2Body * b1, b2Body * b2)
{

	if (o != nullptr){
		//Si lo que ha colisionado con nosotros es una bala, comprobamos si es del jugador o de un enemigo
		if (b2->GetFixtureList()->GetFilterData().categoryBits == Juego::JUGADOR){
			//NOTIFICAR DE QUE SE HA RECOGIDO UNA TARJETA
			pJuego->tarjetasRecogida();
			destruido = true;
		}
	}
}
