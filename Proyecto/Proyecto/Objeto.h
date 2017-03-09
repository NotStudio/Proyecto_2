#ifndef OBJETO_H_
#define OBJETO_H_

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

	virtual void onColisionEnter(Objeto* contactObject)= 0;

	

};

#endif