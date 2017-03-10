#include "contactListener.h"
#include "Tile.h"

void contactListener::BeginContact(b2Contact* contact){


	    void* ob1 =  contact->GetFixtureA()->GetBody()->GetUserData();
		void* ob2 = contact->GetFixtureB()->GetBody()->GetUserData();
		bool ob1Tile = ((Tile*)ob1)->getType() <= 0 || ((Tile*)ob1)->getType() >= 17;
		bool ob2Tile = ((Tile*)ob2)->getType() <= 0 || ((Tile*)ob2)->getType() >= 17;
		if (ob1Tile^ob2Tile) {
			if (ob1Tile) {
				static_cast<Tile*>(ob2)->onColisionEnter();
				static_cast<Objeto*>(ob1)->onColisionEnter(nullptr);
			}
			else if (ob2Tile)
			{
				static_cast<Tile*>(ob1)->onColisionEnter();
				static_cast<Objeto*>(ob2)->onColisionEnter(nullptr);
			}
		}

		else if (ob1 && ob2) {
			static_cast<Objeto*>(ob1)->onColisionEnter((Objeto*)ob2);
			static_cast<Objeto*>(ob2)->onColisionEnter((Objeto*)ob1);
		}
}
