#ifndef INANIMADOINFO_H_
#define INANIMADOINFO_H_
#include <SDL.h>
#include "TileInfo.h"
/*tamaño determinado 7 tiles de ancho, 3 tiles de alto factor es la escala*/
SDL_Rect TuberiaRect(int x=0,int y=0,float escala=1.0f) {
	return SDL_Rect{ x,y,escala*TILE_WIDTH * 7,escala*TILE_HEIGHT * 3 };
}
/*tamaño determinado 1 tile de ancho y 1 tile de alto*/
SDL_Rect AgujeroRect(int x = 0, int y = 0, float escala = 1.0f) {
	return SDL_Rect{ x,y,escala*TILE_WIDTH,escala*TILE_HEIGHT };
}
/*tamaño determinado 5 tile de ancho y 3 tile de alto*/
SDL_Rect NaveRect(int x = 0, int y = 0, float escala = 1.0f) {
	return SDL_Rect{ x,y,escala*TILE_WIDTH * 5,escala*TILE_HEIGHT * 3 };
}
/*tamaño determinado 5 tile de ancho y 3 tile de alto*/
SDL_Rect ChatarraRect(int x = 0, int y = 0, float escala = 1.0f) {
	return SDL_Rect{ x,y,escala*TILE_WIDTH *5,escala*TILE_HEIGHT * 3 };
}
#endif // !INANIMADOINFO_H_
