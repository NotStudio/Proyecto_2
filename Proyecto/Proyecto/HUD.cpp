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


	maxVidas = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vidaMax;

	medAncho = (ancho + 0.0) / 64;
	medAlto = (alto + 0.0) / 32;

	statVelMov = new HUDText(pjuego, 5.5*medAncho, medAlto *23,"NULL");
	statDanyo = new HUDText(pjuego, 5.5*medAncho, medAlto *26,  "NULL");
	statVelAtaq = new HUDText(pjuego, 5.5*medAncho, medAlto*29,  "NULL");


	marcoStats = new HUDImage(pjuego, 0, medAlto * 22, 13 * medAncho, alto, "marco");

	velMov = new  HUDImage(pjuego, 0.5 * medAncho, medAlto*23, medAncho*5, medAlto * 25, "velmov");
	ataque = new HUDImage(pjuego, 0.5*medAncho, medAlto *26, 5* medAncho, medAlto * 28, "ataque");
	velAtaq = new HUDImage(pjuego, 0.5*medAncho, medAlto *29, 5* medAncho, medAlto * 31, "velataq");
	vida = new HUDImage(pjuego, "vida");



	fondoVida = new HUDImage(pjuego, 3, 3, (4*medAncho*maxVidas) + medAncho*2, 3 * medAlto, "fondovida");
	cables = new HUDImage(pjuego, 0, 0, ancho, alto, "cables");

	statVelMov->setTamanyo(10);
	statDanyo->setTamanyo(10);
	statVelMov->setTamanyo(25);

	statVelMov->cambiaFuente("hudfont");
	statDanyo->cambiaFuente("hudfont");
	statVelAtaq->cambiaFuente("hudfont");

	updateHUD();
}


HUD::~HUD()
{
	delete marcoStats;


	delete statDanyo, statVelAtaq, statVelMov;
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

	fondoVida->draw();
	for (size_t i = 0; i < vidasAct; i++){
		vida->draw(5 + (i*(fondoVida->getPos().w-30 / maxVidas))+5, 7, (i + 1)*(fondoVida->getPos().w-30 / maxVidas)-5, 3 * medAlto - 5);
	}

	//vidas.draw();
}
void HUD::updateHUD(){
	Jugable * aux = static_cast<Jugable*>(pjuego->getActiveCharacter());
	vidasAct = static_cast<Jugable*>(pjuego->getActiveCharacter())->getStats()->vida;

	statVelMov->setTexto(to_string(aux->getStats()->velMov).substr(0, 3));
	statDanyo->setTexto(to_string(aux->getStats()->daño).substr(0, 4));
	statVelAtaq->setTexto(to_string(aux->getStats()->velAtq).substr(0, 4));


}
