#include "BalaEnemiga.h"


BalaEnemiga::BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry) : Bala(punteroJuego, spritePar, "BalaN", vel, dirx, diry, 1)
{
}

BalaEnemiga::BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry) : Bala(punteroJuego, spritePar, objectId, vel, dirx, diry, 1)
{
}

BalaEnemiga::~BalaEnemiga()
{
}
