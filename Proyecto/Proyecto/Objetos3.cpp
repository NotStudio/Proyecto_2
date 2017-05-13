#include "Objetos3.h"
#include "checkML.h"


Objetos3::Objetos3(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Fondo = pJuego->getTextura("HudCraft3", "idle");
	botones.emplace_back(new Boton(pJuego, "button", 20, 50, mecanismo, "Mecanismo"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 100, combustible, "Combustible"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 150, fibraCarbono, "FibraCarbono"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 200, moduloComandos, "ModuloComandos"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 250, mensaje, "Eje"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 300, mensaje, "Pantalla"));
	//botones.emplace_back(new Boton(pJuego, "boton", 50, 200, mensaje, "ModuloComados"));
	botones.emplace_back(new Boton(pJuego, "button", 575, 475, salir, "Salir"));
	img = pJuego->getTextura(botones[0]->getNombre(), "idle");

	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));
}


Objetos3::~Objetos3()
{
}

void Objetos3::draw() {
	MenuJuego::draw();

	if (botones[activo]->getNombre() != "Salir"){
		
		img->draw(pJuego->getRender(), SDL_Rect{ 530, 20, 125, 125 }, nullptr);
		receta(botones[activo]->getNombre());
		Texto.draw(pJuego->getRender(), 650, 50);
	}
	else{

	}

}

void Objetos3::update() {
	MenuJuego::update();
	if (botones[activo]->getNombre() != "Salir") {
		img = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())) {
			Texto.loadTexto(pJuego->getRender(), "0");
		}
		else {
			Texto.loadTexto(pJuego->getRender(),std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
		}
	}
	

}


void Objetos3::salir(Juego* pJuego) {


	pJuego->popState();


}

void Objetos3::combustible(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Petroleo") && pjuego->getBaul()->getCantidad("Petroleo") >= 1) &&

		(pjuego->getBaul()->findItem("Refinador") && pjuego->getBaul()->getCantidad("Refinador") >= 1)){

		pjuego->getBaul()->insertItem("Combustible", 1);
		pjuego->getBaul()->removeItem("Petroleo", 1);
		pjuego->getBaul()->removeItem("Refinador", 1);

	}

}
void Objetos3::mecanismo(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Engranajes") && pjuego->getBaul()->getCantidad("Engranajes") >= 1) &&

		(pjuego->getBaul()->findItem("Eje") && pjuego->getBaul()->getCantidad("Eje") >= 1) &&
		
		(pjuego->getBaul()->findItem("Fusible") && pjuego->getBaul()->getCantidad("Fusible") >= 1)){

		pjuego->getBaul()->insertItem("Mecanismo", 1);
		pjuego->getBaul()->removeItem("Engranajes", 1);
		pjuego->getBaul()->removeItem("Eje", 1);
		pjuego->getBaul()->removeItem("Fusible", 1);

	}
}
void Objetos3::fibraCarbono(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Carbono") && pjuego->getBaul()->getCantidad("Carbono") >= 1) &&

		(pjuego->getBaul()->findItem("Madera") && pjuego->getBaul()->getCantidad("Madera") >= 1)){//y algo	que dropea el 1er boss...

		pjuego->getBaul()->insertItem("FibraCarbono", 1);
		pjuego->getBaul()->removeItem("Carbono", 1);
		pjuego->getBaul()->removeItem("Madera", 1);

	}
}

void Objetos3::moduloComandos(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Pantalla") && pjuego->getBaul()->getCantidad("Pantalla") >= 1) &&

		(pjuego->getBaul()->findItem("Circuito") && pjuego->getBaul()->getCantidad("Circuito") >= 2)){

		pjuego->getBaul()->insertItem("ModuloComandos", 1);
		pjuego->getBaul()->removeItem("Pantalla", 1);
		pjuego->getBaul()->removeItem("Circuito", 2);

	}

}

void Objetos3::mensaje(Juego* pjuego){

	std::cout << "lo dropea un boss";
}


void Objetos3::receta(std::string obj){
	
	if (obj == "Mecanismo"){
		pJuego->getTextura("Engranajes", "idle")->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Eje", "idle")->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Fusible", "idle")->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, nullptr, 0.0);
	}
	else if (obj == "Combustible"){
		pJuego->getTextura("Petroleo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Petroleo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Refinador", "idle")->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, nullptr, 0.0);
	}

	else if (obj == "FibraCarbono"){
		pJuego->getTextura("Carbono", "idle")->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Madera", "idle")->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, nullptr, 0.0);
		/*pJuego->getTextura("Madera", "idle")->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, nullptr, 0.0);*/
	}

	else if (obj == "ModuloComandos"){
		pJuego->getTextura("Pantalla", "idle")->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, nullptr, 0.0);
		
		pJuego->getTextura("Circuito", "idle")->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, nullptr, 0.0);
		pJuego->getTextura("Circuito", "idle")->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, nullptr, 0.0);
	}

}