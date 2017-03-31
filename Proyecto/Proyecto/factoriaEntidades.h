#ifndef INANIMADOINFO_H_
#define INANIMADOINFO_H_
#include "Entidad.h"
Objeto * creaInanimado(Juego * pj, string id, int x, int y, int w,int h ,float escala = 1);
Objeto * creaEnemigo(Juego * pj, string id, int x, int y, int aditional = 1);
#endif // !INANIMADOINFO_H_
