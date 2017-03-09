#ifndef NPC_H_
#define NPC_H_

#include "Personaje.h"
class NPC :
	public Personaje
{
public:
	NPC(Juego* punteroJuego, SDL_Rect spritePar, string objectId);
	virtual ~NPC();

};

#endif