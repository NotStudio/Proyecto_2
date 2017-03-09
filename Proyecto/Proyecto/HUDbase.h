
#ifndef HUDBASE_H_
#define HUDBASE_H_
#include<SDL.h>

#include "Objeto.h"
class HUDbase
{
public:

	HUDbase()
	{
	}

	virtual ~HUDbase()
	{
	}


	virtual void draw(Objeto* personaje)=0;

	virtual SDL_Rect * getRect() = 0;
		

};
#endif

