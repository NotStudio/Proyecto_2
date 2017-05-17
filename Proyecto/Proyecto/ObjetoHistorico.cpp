#include "ObjetoHistorico.h"
#include "Jugable.h"


ObjetoHistorico::ObjetoHistorico(Juego* punteroJuego, SDL_Rect spritePar, string objectId, int cantidad) : Item(punteroJuego, spritePar, objectId), cantidad_(cantidad)
{
}


ObjetoHistorico::~ObjetoHistorico()
{
}

void ObjetoHistorico::onColisionEnter(Objeto* Contacto, b2Body* b1, b2Body* b2)
{
	if (dynamic_cast<Jugable*>(Contacto)) {
		pJuego->addItemToInventary(id, cantidad_);
		destruido = true;
	}
	
}

