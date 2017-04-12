#ifndef OBJETO_H_
#define OBJETO_H_
#include <Box2D\Box2D.h>


class Objeto
{
public:

	Objeto()
	{
	}

	virtual ~Objeto()
	{
	}

	virtual void update() = 0;

	virtual void draw() = 0;

	virtual void onColisionEnter(Objeto* contactObject, b2Body* b1, b2Body* b2)= 0;

	virtual bool getdestruido() { return false; };

};

#endif