#ifndef INANIMADO_H_
#define INANIMADO_H_


#include "SelecZonaMenu.h"
#include "Entidad.h"
#include "Cambio.h"
#include "Crafteo.h"

class Inanimado :
	public Entidad
{
public:
	Inanimado(Juego * pj, SDL_Rect Tam, string id): Entidad(pj,Tam,id){
		bodyDef.type = b2_staticBody;
		bodyDef.fixedRotation = true;
		bodyDef.position.Set(pos.x, pos.y);
		body = pJuego->getWorld()->CreateBody(&bodyDef);
		body->SetUserData(this);
		if (id == "agujero") {
			shape = new b2CircleShape();
			static_cast<b2CircleShape*>(shape)->m_p = {(float32)sprite->w / 2,(float32)sprite->h / 2 };
			static_cast<b2CircleShape*>(shape)->m_radius= Tam.w/2;
		}
		else {
			shape = new b2PolygonShape;
			static_cast<b2PolygonShape*>(shape)->SetAsBox(sprite->w / 2, sprite->h / 2, { (float)sprite->w / 2, (float)sprite->h / 2 }, 0);
		}
		fDef.shape = shape; fDef.density = 5.0f; fDef.friction = 0;
		
	}
	virtual ~Inanimado() {
		
	};
	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {};
};

//==============================================================================================
//AGUJERO
class Agujero:
	public Inanimado
{
public:
	Agujero(Juego * Pj, int x,int y, int w,int h) :Inanimado(Pj, SDL_Rect{x,y,w,h}, "agujero") {
	
		fDef.filter.categoryBits = Juego::ESCENARIO_NOCOL;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO;
		body->CreateFixture(&fDef);	
	}
	~Agujero() { };
private:

};
//==============================================================================================
//TUBERIA
class Tuberia: public Inanimado
{
public:
	Tuberia(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x,y, w,h }, "Tuberia") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR; 
		body->CreateFixture(&fDef);
	};
	~Tuberia() {};
};
//==============================================================================================
//NAVE
class Nave : public Inanimado
{
public:
	Nave(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x,y, w, h}, "Nave") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Nave() {};
};

//==============================================================================================
//CHATARRA
class Chatarra : public Inanimado
{
public:
	Chatarra(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, w,h }, "Chatarra") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR | Juego::ENEMIGO | Juego::AT_ENEMIGO | Juego::AT_JUGADOR;
		body->CreateFixture(&fDef);
	};
	~Chatarra() {};
};

//==============================================================================================
//SELECTOR DE ZONA
class  SelectorZona : public Inanimado
{
public:
	SelectorZona(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorZona") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorZona() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new SelecZonaMenu(pJuego));
	}
};

//==============================================================================================
//SELECTOR DE Cambio
class  SelectorCambio : public Inanimado
{
public:
	SelectorCambio(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorCambio") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorCambio() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new Cambio(pJuego, pJuego->getActivo(), pJuego->getPersonajes()));
	}
};
	//==============================================================================================
//SELECTOR DE CRAFTEO
class  SelectorCrafteo : public Inanimado
{
public:
	SelectorCrafteo(Juego * Pj, int x, int y, int w, int h) :Inanimado(Pj, SDL_Rect{ x, y, TILE_WIDTH * 4, TILE_HEIGHT * 4 }, "SelectorCrafteo") {
		fDef.filter.categoryBits = Juego::ESCENARIO;
		fDef.filter.maskBits = Juego::JUGADOR;
		body->CreateFixture(&fDef);
	};
	~SelectorCrafteo() {};

	virtual void onColisionEnter(Objeto* o, b2Body* b1, b2Body* b2) {

		pJuego->pushState(new Crafteo(pJuego));
	}
};
#endif // INANIMADO_H_