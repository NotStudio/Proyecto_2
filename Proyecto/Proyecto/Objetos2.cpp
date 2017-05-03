#include "Objetos2.h"


Objetos2::Objetos2(Juego* pJuego) : Crafteo(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "button", 50, 50, engranaje, "Engranaje"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 100, carbono, "Carbono"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 150, engranajes, "Engranajes"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 200, tanquePresion, "TanquePresion"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 250, refinador, "Refinador"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 300, circuito, "Circuito"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 350, bateriaIones, "IonBattery"));
	botones.emplace_back(new Boton(pJuego, "button", 50, 400, sensorMov, "SensorMov"));
	botones.emplace_back(new Boton(pJuego, "button", 575, 475, salir, "Salir"));

	animacion.loadTextura(pJuego->getTextura(botones[0]->getNombre(), "idle"));

	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));

}


Objetos2::~Objetos2()
{
}

void Objetos2::draw() {

	pJuego->getTextura("HudCraft2", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}

	if (botones[activo]->getNombre() != "Salir"){
		animacion.textura = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		if (botones[activo]->getNombre() == "Carbono")
			animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 540, 20, 100, 100 }, animacion.currentRect(), 0.0);
		else
			animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 530, 20, 125, 125 }, animacion.currentRect(), 0.0);

		receta(botones[activo]->getNombre());
		
		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){

			Texto.loadTexto(pJuego->getRender(), "0");
			Texto.draw(pJuego->getRender(), 650, 50);
		}
		else{
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 650, 50);
			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
		}
	}
	else{
		pJuego->getTextura("HudCraft", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);
		for (int i = 0; i < botones.size(); i++)
		{
			botones[i]->draw();
		}
	}

}

void Objetos2::update() {



	botones[activo]->normal();
	if (pJuego->teclaPulsada(SDL_SCANCODE_DOWN)) {

		if (activo < botones.size() - 1) {
			activo++;
		}
	}

	else if (pJuego->teclaPulsada(SDL_SCANCODE_UP)) {
		if (activo > 0) {
			activo--;
		}
	}
	botones[activo]->aumentar();
	if (pJuego->teclaPulsada(SDL_SCANCODE_RETURN)) {
		botones[activo]->accion();
	}

}


void Objetos2::salir(Juego* pJuego) {


	pJuego->popState();


}

void Objetos2::engranaje(Juego* pjuego) {

	if (pjuego->getBaul()->findItem("Chatarra") && (pjuego->getBaul()->getCantidad("Chatarra") >= 2)){

		pjuego->getBaul()->insertItem("Engranaje", 1);
		pjuego->getBaul()->removeItem("Chatarra", 2);

	}
}

void Objetos2::carbono(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Carbon") && pjuego->getBaul()->getCantidad("Carbon") >= 1) &&
		
		(pjuego->getBaul()->findItem("Madera") && pjuego->getBaul()->getCantidad("Madera") >= 1)){

		pjuego->getBaul()->insertItem("Carbono", 1);
		pjuego->getBaul()->removeItem("Carbon", 1);
		pjuego->getBaul()->removeItem("Madera", 1);

	}
}

void Objetos2::engranajes(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Engranaje") && pjuego->getBaul()->getCantidad("Engranaje") >= 1) &&

		(pjuego->getBaul()->findItem("Tuerca") && pjuego->getBaul()->getCantidad("Tuerca") >= 1)){

		pjuego->getBaul()->insertItem("Engranajes", 1);
		pjuego->getBaul()->removeItem("Engranajes", 1);
		pjuego->getBaul()->removeItem("Tuerca", 1);

	}
}

void Objetos2::tanquePresion(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Tanque") && pjuego->getBaul()->getCantidad("Tanque") >= 1) &&

		(pjuego->getBaul()->findItem("Fusible") && pjuego->getBaul()->getCantidad("Fusible") >= 1)){

		pjuego->getBaul()->insertItem("TanquePresion", 1);
		pjuego->getBaul()->removeItem("Tanque", 1);
		pjuego->getBaul()->removeItem("Fusible", 1);

	}
}

void Objetos2::refinador(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("TanquePresion") && pjuego->getBaul()->getCantidad("TanquePresion") >= 1) &&

		(pjuego->getBaul()->findItem("Tuberias") && pjuego->getBaul()->getCantidad("Tuberias") >= 1)){

		pjuego->getBaul()->insertItem("Refinador", 1);
		pjuego->getBaul()->removeItem("TanquePresion", 1);
		pjuego->getBaul()->removeItem("Tuberias", 1);

	}

}

void Objetos2::circuito(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Estaño") && pjuego->getBaul()->getCantidad("Estaño") >= 1) &&

		(pjuego->getBaul()->findItem("Chip") && pjuego->getBaul()->getCantidad("Chip") >= 1)){

		pjuego->getBaul()->insertItem("Circuito", 1);
		pjuego->getBaul()->removeItem("Estaño", 1);
		pjuego->getBaul()->removeItem("Chip", 1);


	}
}

void Objetos2::bateriaIones(Juego* pjuego){


	if ((pjuego->getBaul()->findItem("Estaño") && pjuego->getBaul()->getCantidad("Estaño") >= 1) &&

		(pjuego->getBaul()->findItem("Litio") && pjuego->getBaul()->getCantidad("Litio") >= 1)){

		pjuego->getBaul()->insertItem("IonBattery", 1);
		pjuego->getBaul()->removeItem("Estaño", 1);
		pjuego->getBaul()->removeItem("Litio", 1);

	}
}

void Objetos2::sensorMov(Juego* pjuego){

	if ((pjuego->getBaul()->findItem("Chip") && pjuego->getBaul()->getCantidad("Chip") >= 1) &&

		(pjuego->getBaul()->findItem("Sensor") && pjuego->getBaul()->getCantidad("Sensor") >= 1)){

		pjuego->getBaul()->insertItem("SensorMov", 1);
		pjuego->getBaul()->removeItem("Chip", 1);
		pjuego->getBaul()->removeItem("Sensor", 1);

	}

}


void Objetos2::receta(std::string obj){

	if (obj == "Engranaje"){
		animacion.textura = pJuego->getTextura("Chatarra", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "Carbono"){
		animacion.textura = pJuego->getTextura("Madera", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Carbon", "idle");

		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "Engranajes"){
		animacion.textura = pJuego->getTextura("Engranaje", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Tuercas", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "TanquePresion"){
		animacion.textura = pJuego->getTextura("Tanque", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Fusible", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "Refinador"){
		animacion.textura = pJuego->getTextura("TanquePresion", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Tuberias", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "Circuito"){
		animacion.textura = pJuego->getTextura("Estanyo", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Chip", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if (obj == "IonBattery"){
		animacion.textura = pJuego->getTextura("Estanyo", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Litio", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

	else if ("SensorMov"){
		animacion.textura = pJuego->getTextura("Chip", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, animacion.currentRect(), 0.0);
		animacion.textura = pJuego->getTextura("Sensor", "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, animacion.currentRect(), 0.0);
	}

}

 
