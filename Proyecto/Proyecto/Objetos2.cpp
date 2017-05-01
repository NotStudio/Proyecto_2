#include "Objetos2.h"


Objetos2::Objetos2(Juego* pJuego) : Crafteo(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "boton", 50, 50, engranaje, "Engranaje"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 100, carbono, "Carbono"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 150, engranajes, "Engranajes"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 200, tanquePresion, "TanquePresion"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 250, refinador, "Refinador"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 300, circuito, "Circuito"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 350, bateriaIones, "IonBattery"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 400, sensorMov, "SensorMov"));
	botones.emplace_back(new Boton(pJuego, "boton", 400, 300, salir, "Salir"));
	animacion.loadTextura(pJuego->getTextura(botones[0]->getNombre(), "idle"));

}


Objetos2::~Objetos2()
{
}

void Objetos2::draw() {

	pJuego->getTextura("SelecMapaFondo", "idle")->draw(pJuego->getRender(), SDL_Rect{ 0, 0, 800, 600 }, nullptr);//PROVISIONAL

	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}

	if (botones[activo]->getNombre() != "Salir"){
		animacion.textura = pJuego->getTextura(botones[activo]->getNombre(), "idle");
		animacion.textura->draw(pJuego->getRender(), SDL_Rect{ 400, 75, 150, 150 }, animacion.currentRect(), 0.0);
		
		if (!pJuego->getBaul()->findItem(botones[activo]->getNombre())){

			//escribir texto con cantidad 0
			std::cout << "0";
		}
		else{
			// escribit esto con texto pJuego->getBaul()->getCantidad(botones[activo]->getNombre());

			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
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

		std::cout << "LOKOOOOOOOOOOOOO ";

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


 
