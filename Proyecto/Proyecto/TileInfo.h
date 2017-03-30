#ifndef TILEINFO_H_
#define TILEINFO_H_

const int TILE_WIDTH = 64, TILE_HEIGHT = 64;
const int TOTAL_TILES = 36;
enum TiposTile
{
	S1 = 0, S2 = 1, S3 = 2, S4 = 3,
	S5 = 4, S6 = 5, S7 = 6, S8 = 7,
	S9 = 8, S10 = 9, S11 = 10, S12 = 11,
	PO = 12, PN=13, PS = 14, PE = 15,
	ENO = 16, ENE = 17, ESE = 18, ESO = 19,
	INO = 20, INE = 21, ISO = 22, ISE = 23,
	MH = 24, MV= 25, PUN = 26, PUE = 27,
	PUO = 28, PUS = 29, CRZ = 30, TI = 31,
	T = 32, TE = 33, TO = 34, NOT = 35,
};

//Norte = 0, Este = 1, Sur = 2, Oeste = 3, Sinsitio = 4,
enum Direcciones
{
	Norte = 1, Este = 2, Sur = -1, Oeste = -2, Sinsitio = 0
};
struct Puerta{
	Direcciones DirPuerta;
	SDL_Rect posicion;
	SDL_Rect zonaPuerta;
};
#endif