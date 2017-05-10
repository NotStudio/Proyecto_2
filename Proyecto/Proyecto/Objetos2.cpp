#include "Objetos2.h"


Objetos2::Objetos2(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("HudCraft2", "idle");
	botones.emplace_back(new Boton(pJuego, "button", 20, 50, engranaje, "Engranaje"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 100, carbono, "Carbono"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 150, engranajes, "Engranajes"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 200, tanquePresion, "TanquePresion"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 250, refinador, "Refinador"));
	botones.emplace_back(new Boton(pJuego, "button", 20, 300, circuito, "Circuito"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 50, bateriaIones, "IonBattery"));
	botones.emplace_back(new Boton(pJuego, "button", 190, 100, sensorMov, "SensorMov"));
	botones.emplace_back(new Boton(pJuego, "button", 565, 470, salir, "Salir"));

	img = pJuego->getTextura(botones[0]->getNombre(), "idle");

	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));

}


Objetos2::~Objetos2()
{
}

void Objetos2::draw() {
	MenuJuego::draw();

	if (botones[activo]->getNombre() != "Salir"){
		img = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		if (botones[activo]->getNombre() == "Carbono")
			img->draw(pJuego->getRender(), SDL_Rect{ 540, 20, 100, 100 }, nullptr, 0.0);
		else
			img->draw(pJuego->getRender(), SDL_Rect{ 530, 20, 125, 125 }, nullptr, 0.0);

		receta(botones[activo]->getNombre());
		
		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){

			Texto.loadTexto(pJuego->getRender(), "0");
			Texto.draw(pJuego->getRender(), 650, 50);
		}
		else{
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 650, 50);
		}
	}
	else{
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
	TexturasSDL * T1=nullptr, * T2=nullptr;
	if (obj == "Engranaje"){
		T1 = pJuego->getTextura("Chatarra", "idle");
		T2 = T1;
	}

	else if (obj == "Carbono"){
		T1 = pJuego->getTextura("Madera", "idle");
		T2 = pJuego->getTextura("Carbon", "idle");

	}

	else if (obj == "Engranajes"){
		T1 = pJuego->getTextura("Engranaje", "idle");
		T2 =pJuego->getTextura("Tuercas", "idle");
	}

	else if (obj == "TanquePresion"){
		T1 = pJuego->getTextura("Tanque", "idle");
		T2 = pJuego->getTextura("Fusible", "idle");
	}

	else if (obj == "Refinador"){
		T1 = pJuego->getTextura("TanquePresion", "idle");
		T2 = pJuego->getTextura("Tuberias", "idle");
	}

	else if (obj == "Circuito"){
		T1 = pJuego->getTextura("Estanyo", "idle");
		T2 = pJuego->getTextura("Chip", "idle");
	}

	else if (obj == "IonBattery") {
		T1 = pJuego->getTextura("Estanyo", "idle");

		T2 = pJuego->getTextura("Litio", "idle");
	}
	else if ("SensorMov"){
		T1 = pJuego->getTextura("Chip", "idle");
		T2 = pJuego->getTextura("Sensor", "idle");
		
	}
	if (T1 != nullptr) {
		T1->draw(pJuego->getRender(), SDL_Rect{ 650, 260, 100, 100 }, nullptr);
		T2->draw(pJuego->getRender(), SDL_Rect{ 425, 260, 100, 100 }, nullptr);
	}

}

 
