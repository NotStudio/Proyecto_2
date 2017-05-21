#pragma once
class HUDObjeto
{
public:
	HUDObjeto();
	virtual ~HUDObjeto();
protected:
	virtual void draw() = 0;
	virtual void draw(int x, int y) = 0;
};

