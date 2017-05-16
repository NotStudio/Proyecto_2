#include "HUDText.h"


HUDText::HUDText() : txt(nullptr)
{
}
HUDText::HUDText(Juego * pJuego, string texto): HUDObj(){
	pJuego = pJuego;
	pRend = pJuego->getRender();
	txt->loadTexto(pRend, texto);
}
HUDText::HUDText(Juego * pJ, string tx, int tamano, SDL_Color clr , string fte): fuente(new Fuente()), txt (new TextoSDL()){
	pJuego = pJ;
	nFuente = fte;
	color = clr;
	tam = tamano;
	texto = tx;
	fuente = pJuego->getTipografia(fte);
	pRend = pJuego->getRender();
	fuente->loadFuente(fuente->fichero, tam);
	txt->LoadFuente(fuente);
	txt->loadTexto(pRend, texto, color);
}


void HUDText::draw(int x1, int y1, int x2, int y2){
	pos = SDL_Rect{ x1, y1, x2, y2 };
	txt->draw(pRend, pos.x, pos.y);
}
void HUDText::draw(){
	txt->draw(pRend, pos.x, pos.y);
}
void HUDText::setTexto(string aux){
	texto = aux;
	txt->loadTexto(pRend, texto, color);
}
void HUDText::setColor(SDL_Color aux){
	color = aux;
	txt->loadTexto(pRend, texto, color);
}
void HUDText::cambiaFuente(string fnte){
	nFuente = fnte;
	fuente = pJuego->getTipografia(fnte, tam);
	fuente->loadFuente(fnte, tam);
	txt->LoadFuente(fuente);
}
void HUDText::setTamanyo(int auxx){
	tam = auxx;
	fuente->loadFuente(nFuente, tam);
	
}
HUDText::~HUDText()
{
	delete fuente;
	delete txt;
}
