#pragma once
#include "..\Box2D\include\Box2D\Dynamics\b2WorldCallbacks.h"
#include "..\Box2D\include\Box2D\Dynamics\Contacts\b2Contact.h"
#include "Objeto.h"
class contactListener :
	public b2ContactListener
{
public:

	void beginContact(b2Contact* contact);
};

