#ifndef CONTACT_LISTENER_H_
#define CONTACT_LISTENER_H_
#include "..\Box2D\include\Box2D\Dynamics\b2WorldCallbacks.h"
#include "..\Box2D\include\Box2D\Dynamics\Contacts\b2Contact.h"
class contactListener :
	public b2ContactListener
{
public:

	void BeginContact(b2Contact* contact);
};

#endif