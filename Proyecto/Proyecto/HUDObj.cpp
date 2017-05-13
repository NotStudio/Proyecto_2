#include "HUDObj.h"


HUDObj::HUDObj() :active(false), pos(SDL_Rect{ 0, 0, 0, 0 }), pJuego(nullptr), pRend(nullptr)
{
}


HUDObj::~HUDObj()
{
}
