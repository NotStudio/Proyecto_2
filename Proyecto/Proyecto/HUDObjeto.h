#pragma once
class HUDObjeto
{
public:
	HUDObjeto();
	virtual ~HUDObjeto();
protected:
	virtual void draw() = 0;
	virtual void draw(int x, int y) = 0;
	virtual void draw(int x, int y, int x1, int y1) = 0;
};

