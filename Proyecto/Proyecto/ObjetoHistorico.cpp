#include "ObjetoHistorico.h"


ObjetoHistorico::ObjetoHistorico(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int cantidad) : Item(punteroJuego, spritePar, objectId), cantidad_(cantidad)
{
}


ObjetoHistorico::~ObjetoHistorico()
{
}

void ObjetoHistorico::onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2)
{
	
}
