#pragma once

const int TILE_WIDTH = 50, TILE_HEIGHT = 50;
enum TiposTile
{
	S1 = 0, S2 = 1, S3 = 2, S4 = 3,
	PV = 4, PH = 5, NE = 6, SE = 7,
	NO = 8, SO = 9, IP = 10, NA = 11
};
struct Direcciones{
	bool Norte, Sur, Este, Oeste;
};