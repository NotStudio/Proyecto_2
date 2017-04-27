#include "BalaAmiga.h"


BalaAmiga::BalaAmiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry, int danyo) : Bala(punteroJuego, spritePar,"DisparoToasty", vel, dirx, diry, 0), danyo(danyo)
{
}


BalaAmiga::~BalaAmiga()
{
}
