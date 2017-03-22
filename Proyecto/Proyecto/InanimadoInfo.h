#ifndef INANIMADOINFO_H_
#define INANIMADOINFO_H_
#include <SDL.h>
#include "TileInfo.h"
#include "Inanimado.h"
#include "Enemigo.h"
Inanimado * creaInanimado(Juego * pj, string id, int x, int y, float escala = 1);
Enemigo * creaEnemigo(Juego * pj, string id, int x, int y, int aditional = 1);
#endif // !INANIMADOINFO_H_
