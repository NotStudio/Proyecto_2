#include "BalaAmiga.h"


BalaAmiga::BalaAmiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry) : Bala(punteroJuego, spritePar,"DisparoToasty", vel, dirx, diry, 0)
{
}


BalaAmiga::~BalaAmiga()
{
}
