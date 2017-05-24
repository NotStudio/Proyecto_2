#ifndef INANIMADOINFO_H_
#define INANIMADOINFO_H_
#include "Entidad.h"
#include "MapData.h"
Objeto * creaInanimado(Juego * pj, string id, int x, int y, int w,int h ,float escala = 1);
Objeto * creaEnemigo(Juego * pj, string id, int x, int y, TMXReader::Properties * properties);
Objeto * creaEntidad(Juego * pj, TMXReader::ObjectInfo * obj, int desvX, int desvY);
#endif // !INANIMADOINFO_H_
