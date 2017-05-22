#include "HUD.h"
#include "Jugable.h"


HUD::HUD(Juego* punteroJuego, SDL_Rect spritePar, string objectId, string objectAnim) : pjuego(punteroJuego), statDanyo(), statVelMov(), statVelAtaq()
{
	id = objectId;
	anim = objectAnim;// Para las vidas esto tiene que ser: "Cuatro", solo al principio
	animacion.loadTextura(pjuego->getTextura(id, anim));
	// No se si el nombre este tiene que tener longitud 4, 
	//porque en juego initMedia() se hace substr de una cadena de 4 caracteres.
	sprite = new SDL_Rect(spritePar);


	int ancho = pjuego->getWindow().ancho;
	int alto = pjuego->getWindow().alto;


	
	

	medAncho = (ancho + 0.0) / 64;
	medAlto = (alto + 0.0) / 32;

	statVelMov = new HUDText(pjuego, 5.5*medAncho, medAlto * 24, "hudfont");
	statDanyo = new HUDText(pjuego, 5.5*medAncho, medAlto * 27, "hudfont");
	statVelAtaq = new HUDText(pjuego, 5.5*medAncho, medAlto * 30,  "hudfont");
	


	marcoStats = new HUDImage(pjuego, 0, medAlto * 22, 11 * medAncho, alto, "marco");

	velMov = new  HUDImage(pjuego, 0.5 * medAncho, medAlto*23, medAncho*4.5, medAlto * 25, "velmov");
	ataque = new HUDImage(pjuego, 0.5*medAncho, medAlto *26, 4.5* medAncho, medAlto * 28, "ataque");
	velAtaq = new HUDImage(pjuego, 0.5*medAncho, medAlto *29, 4.5* medAncho, medAlto * 31, "velataq");
	vida = new HUDImage(pjuego, "vida");



	fondoVida = new HUDImage(pjuego, 3, 3, (33*medAncho)+6 + medAncho*2.5+5, 3.5 * medAlto, "fondovida");
	cables = new HUDImage(pjuego, 0, 0, ancho, alto, "cables");
	updateHUD();
}

HUD::~HUD()
{
	delete statDanyo, statVelAtaq, statVelMov;
	delete velMov, ataque, velAtaq, cables;
	delete marcoStats;
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
	int x0 = fondoVida->getPos().x+5;
	int y0 = fondoVida->getPos().y;
	int separacion = 1;
	int anchoseccion = fondoVida->getPos().w / maxVidas;
	int anchobarra = anchoseccion - separacion;

	fondoVida->draw();

	for (size_t i = 0; i < vidasAct; i++){
		if (i>vidasAct - 1)separacion = 0;
		vida->draw(x0+(i * (anchobarra)), 3 + medAlto*0.25, x0 + ((i+1)*anchobarra) - separacion, (medAlto * 3.25));
	
	}

	//vidas.draw();
}
void HUD::updateHUD(){
	maxVidas = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vidaMax;
	Jugable * aux = static_cast<Jugable*>(pjuego->getActiveCharacter());
	vidasAct = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vida;

	

	statVelMov->setTexto(to_string(aux->getStats()->velMov).substr(0, 3));
	statDanyo->setTexto(to_string(aux->getStats()->daño).substr(0, 4));
	statVelAtaq->setTexto(to_string(aux->getStats()->velAtq).substr(0, 4));

}
