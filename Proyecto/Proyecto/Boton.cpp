#include "Boton.h"


Boton::Boton(Juego* juego, string ID, int x, int y, CallBack_t * cbCons, string Nombre,string Descripcion )
{
	realRect.x = x;
	realRect.y = y;
	nombre = Nombre;
	id = ID;
	descripcion_ = Descripcion;
	angulo = 0;
	pjuego = juego;
	Anim = pjuego->getAnimaciones(ID).begin()->second;
	cb = cbCons;
	Texto = TextoSDL();
	Texto.LoadFuente(pjuego->getTipografia("Acme____",16));
	Texto.loadTexto(pjuego->getRender(), nombre);

}

Boton::Boton(Juego * juego, string ID, SDL_Rect rect, CallBack_t * cbCons, string texto, string descripcion):Boton(juego,ID,rect.x,rect.y,cbCons,texto,descripcion)
{
	realRect.w = rect.w;
	realRect.h = rect.h;	
}


Boton::~Boton()
{
	delete Anim;
}

void Boton::draw(){
	Anim->draw(pjuego->getRender(), realRect);
	Texto.draw(pjuego->getRender(), realRect.x+(realRect.w- Texto.getAncho())/2, realRect.y+ (realRect.h - Texto.getAlto()) / 2);
}

void Boton::activo(){
	BState_ = BUTTONSTATE_::SELECTED;
}
void Boton::normal(){
	BState_ = BUTTONSTATE_::NOT_SELECTED;
}
void Boton::update(){
	if (BState_) {
		Anim->ActualizarFrame();
	}
	else {

	}
}




BotonMecanico::BotonMecanico(Juego * juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion) :Boton(juego, "buttonSelecZona", { x, y , 176,152}, cbCons, Nombre, descripcion)
{
	Anim->setNumFrames(10);
	
}

void BotonMecanico::update()
{
	if (BState_) {
		Anim->ActualizarFrame();
	}
	else {

	}
}

BotonFuturista::BotonFuturista(Juego * juego, int x, int y, CallBack_t * cbCons, string Nombre, string descripcion):Boton(juego, "Button1", { x, y , 159,58 }, cbCons, Nombre, descripcion)
{
	Anim->setNumFrames(10);
}

void BotonFuturista::update()
{
	if (BState_) {
		if(!Anim->animacionAcabada())
			Anim->ActualizarFrame();
	}
	else {
		if (!Anim->primerFrame())
			Anim->AnteriorFrame();
	}
}


