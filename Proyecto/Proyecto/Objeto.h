#pragma once


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

	virtual bool getDestruido() { return false; };

};

