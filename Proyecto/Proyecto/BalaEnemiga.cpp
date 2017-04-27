#include "BalaEnemiga.h"


BalaEnemiga::BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, float32 vel, float32 dirx, float32 diry, int danyo) : Bala(punteroJuego, spritePar, "BalaN", vel, dirx, diry, 1), danyo(danyo)
{
}

BalaEnemiga::BalaEnemiga(Juego* punteroJuego, SDL_Rect spritePar, string objectId, float32 vel, float32 dirx, float32 diry, int danyo) : Bala(punteroJuego, spritePar, objectId, vel, dirx, diry, 1), danyo(danyo)
{
}

BalaEnemiga::~BalaEnemiga()
{
}
