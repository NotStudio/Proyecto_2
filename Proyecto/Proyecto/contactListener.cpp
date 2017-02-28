#include "contactListener.h"

void contactListener::BeginContact(b2Contact* contact){


	    void* ob1 =  contact->GetFixtureA()->GetBody()->GetUserData();
		void* ob2 = contact->GetFixtureB()->GetBody()->GetUserData();

		if (ob1 && ob2) {
			static_cast<Objeto*>(ob1)->onColisionEnter((Objeto*)ob2);
			static_cast<Objeto*>(ob2)->onColisionEnter((Objeto*)ob1);
		}
}
