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
HUDText::HUDText(Juego * pJ, int x1, int y1, string nFont):txt(new TextoSDL()), tam(17){
	pJuego = pJ;
	texto = "TEXT NOT SET";
	pos = SDL_Rect{ x1, y1, txt->getAncho(), txt->getAlto()};
	
	fuente = pJuego->getTipografia(nFont,tam);
	pRend = pJuego->getRender();
	fuente->loadFuente(fuente->fichero, tam);
	txt->LoadFuente(fuente);
	txt->loadTexto(pRend, texto, color);
}
/*Constructora que recibe el puntero al juego, las coordenadas de inicio y final del rectangulo y el nombre de la fuente*/
HUDText::HUDText(Juego * pJuego, int x1, int y1, int x2, int y2, string font) :txt(new TextoSDL()), tam(25){
	pJuego = pJuego;
	texto = "TEXT NOT SET";
	pos = SDL_Rect{ x1, y1, x2 - x1, y2 - y1 };

	nFuente = font;
	fuente = pJuego->getTipografia(font,tam);
	pRend = pJuego->getRender();
	fuente->loadFuente(fuente->fichero, tam);
	txt->LoadFuente(fuente);
	txt->loadTexto(pRend, texto, color);

}

/*Este metodo dibujará el texto en todo el ancho de la textura*/
void HUDText::draw(int x1, int y1){
	pos = SDL_Rect{ x1, y1, txt->getAncho(), txt->getAlto() };
	txt->draw(pRend, pos.x, pos.y);
}

void HUDText::draw(){
	txt->draw(pRend, pos.x, pos.y);
}
void HUDText::draw(string text){
	setTexto(text);
	draw();
}
/*Este metodo recibe las coordenadas de inicio (x e y) y final del rectangulo (x1 y1)
*/
void HUDText::draw(int x, int y, int x1, int y1){
	SDL_Rect aux{ x, y, x1 - x, y1 - y };
	txt->draw(pRend, aux);


};

void HUDText::setTexto(string aux){
	texto = aux;
	//txt->LoadFuente(pJuego->getTipografia(nFuente));
	txt->loadTexto(pRend, aux, color);
}
void HUDText::setColor(SDL_Color aux){
	color = aux;
	txt->LoadFuente(pJuego->getTipografia(nFuente));
	txt->loadTexto(pRend, texto, color);
}
void HUDText::cambiaFuente(string fnte){
	nFuente = fnte;
	txt->LoadFuente(pJuego->getTipografia(nFuente));
	txt->loadTexto(pRend, texto, color);
}
void HUDText::setTamanyo(int auxx){
	tam = auxx;
	fuente = pJuego->getTipografia(nFuente, tam);
	fuente->loadFuente(fuente->fichero, tam);
	txt->LoadFuente(fuente);
	txt->loadTexto(pRend, texto, color);
}
HUDText::~HUDText()
{
	fuente = nullptr;
	delete txt;
}
