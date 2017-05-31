#include "HUD.h"
#include "Jugable.h"


HUD::HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim) : pjuego(punteroJuego), statDanyo(), statVelMov(), statVelAtaq()
{
	id = objectId;
	anim = objectAnim;// Para las vidas esto tiene que ser: "Cuatro", solo al principio
	animacion.loadTextura(pjuego->getTextura(id, anim));
	// No se si el nombre este tiene que tener longitud 4, 
	//porque en juego initMedia() se hace substr de una cadena de 4 caracteres.


	int ancho = pjuego->getWindow().ancho;
	int alto = pjuego->getWindow().alto;


	
	

	medAncho = (ancho + 0.0) / 64;
	medAlto = (alto + 0.0) / 32;
	SDL_Color color = { 1.0, 1.0, 1.0 };
	statVelMov = new HUDText(pjuego, 5.5*medAncho, medAlto * 19, "hudfont");
	statVelMov->setColor(color);
	statDanyo = new HUDText(pjuego, 5.5*medAncho, medAlto * 22, "hudfont");
	statDanyo->setColor(color);
	statVelAtaq = new HUDText(pjuego, 5.5*medAncho, medAlto * 25,  "hudfont");
	statVelAtaq->setColor(color);
	VidaGui = new HUDText(pjuego, 150,10, "hudfont");
	VidaGui->setColor(color);
	


	marcoStats = new HUDImage(pjuego, -100, medAlto * 17,11 * medAncho, alto -50, "marco");

	velMov = new  HUDImage(pjuego, 0.5 * medAncho, medAlto*19, medAncho*4.5, medAlto * 21, "velmov");
	ataque = new HUDImage(pjuego, 0.5*medAncho, medAlto *22, 4.5* medAncho, medAlto * 25, "ataque");
	velAtaq = new HUDImage(pjuego, 0.5*medAncho, medAlto *25, 4.5* medAncho, medAlto * 28, "velataq");
	vida = new HUDImage(pjuego, "vida");



	fondoVida = { 0,0,400,60 };
	cables = new HUDImage(pjuego, 0, 0, ancho, alto, "cables");
	updateHUD();
}

HUD::~HUD()
{
	delete statDanyo;
	delete statVelAtaq;
	delete statVelMov;
	delete velMov;
	delete ataque;
	delete velAtaq; 
	delete cables;
	delete vida;
	delete marcoStats;
	delete VidaGui;
	pjuego = nullptr;
}

void HUD::draw(){
	updateHUD();
	cables->draw();
	marcoStats->draw();
	statVelMov->draw();
	statDanyo->draw();
	statVelAtaq->draw();


	velAtaq->draw();
	velMov->draw(); 
	ataque->draw();
	int x0 = fondoVida.x+5;
	int y0 = fondoVida.y+5;
	int separacion = 1;
	int anchoseccion = fondoVida.w / maxVidas;
	int anchobarra = anchoseccion - separacion;
	
	SDL_Rect barraVida{x0,y0,anchoseccion*vidasAct-10,50};
	SDL_SetRenderDrawColor(pjuego->getRender(), 47, 79, 79, 255);
	SDL_RenderFillRect(pjuego->getRender(), &fondoVida);

	SDL_SetRenderDrawColor(pjuego->getRender(), 0, 200, 75, 100);

	SDL_RenderFillRect(pjuego->getRender(), &barraVida);

	SDL_SetRenderDrawColor(pjuego->getRender(), 119, 136, 153, 255);
	SDL_RenderDrawRect(pjuego->getRender(), &barraVida);
	SDL_RenderDrawRect(pjuego->getRender(), &fondoVida);


	SDL_SetRenderDrawColor(pjuego->getRender(), 0, 0, 0, 255);
	VidaGui->draw();	


}
void HUD::updateHUD(){
	maxVidas = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vidaMax;
	Jugable * aux = static_cast<Jugable*>(pjuego->getActiveCharacter());
	vidasAct = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vida;

	

	statVelMov->setTexto(to_string(aux->getStats()->velMov).substr(0, 3));
	statDanyo->setTexto(to_string(aux->getStats()->daño).substr(0, 4));
	statVelAtaq->setTexto(to_string(aux->getStats()->velAtq).substr(0, 4));
	VidaGui->setTexto(std::to_string(vidasAct)+" / "+ std::to_string(maxVidas));

}
