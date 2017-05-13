#pragma once
class HUDObjeto
{
public:
	HUDObjeto();
	virtual ~HUDObjeto();
protected:
	virtual void draw(int x, int y, int x1, int x2) = 0;
	virtual void draw() = 0;
};

