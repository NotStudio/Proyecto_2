#include "contactListener.h"
#include "Tile.h"
#include "TileInfo.h"
#include"checkML.h"

void contactListener::BeginContact(b2Contact* contact){


	    void* ob1 =  contact->GetFixtureA()->GetBody()->GetUserData();
		void* ob2 = contact->GetFixtureB()->GetBody()->GetUserData();
		bool ob1Tile = ((Tile*)ob1)->getType() > S12 && ((Tile*)ob1)->getType() < 1+TOTAL_TILES;
		bool ob2Tile = ((Tile*)ob2)->getType() > S12 && ((Tile*)ob2)->getType() < 1+TOTAL_TILES;
		if (ob1Tile^ob2Tile) {
			if (ob1Tile) {
				static_cast<Tile*>(ob1)->onColisionEnter();
				static_cast<Objeto*>(ob2)->onColisionEnter(nullptr, contact->GetFixtureB()->GetBody(), contact->GetFixtureA()->GetBody());
			}
			else if (ob2Tile)
			{
				static_cast<Tile*>(ob2)->onColisionEnter();
				static_cast<Objeto*>(ob1)->onColisionEnter(nullptr, contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody());
			}
		}

		else if (ob1 && ob2) {
			static_cast<Objeto*>(ob1)->onColisionEnter((Objeto*)ob2, contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody()); 
			static_cast<Objeto*>(ob2)->onColisionEnter((Objeto*)ob1, contact->GetFixtureB()->GetBody(), contact->GetFixtureA()->GetBody());
		}
			//1º objeto con el que se colisiona
			//2º el body propio
			//3º el body del objeto con el que se colisiona
}
