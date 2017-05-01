#include "Objetos3.h"


Objetos3::Objetos3(Juego* pJuego) : Crafteo(pJuego)
{

	botones.emplace_back(new Boton(pJuego, "boton", 50, 50, mecanismo, "Mecanismo"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 150, combustible, "Combustible"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 200, fibraCarbono, "FibraCarbono"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 250, moduloComandos, "ModuloComandos"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 300, mensaje, "Eje"));
	botones.emplace_back(new Boton(pJuego, "boton", 50, 350, mensaje, "Pantalla"));
	//botones.emplace_back(new Boton(pJuego, "boton", 50, 200, nullptr, "ModuloComados"));
	botones.emplace_back(new Boton(pJuego, "boton", 400, 300, salir, "Salir"));
	animacion.loadTextura(pJuego->getTextura(botones[0]->getNombre(), "idle"));

	Texto.LoadFuente(pJuego->getTipografia("lazy", 20));
	Texto.loadTexto(pJuego->getRender(), "0");
}


Objetos3::~Objetos3()
{
}

void Objetos3::draw() {

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
			Texto.draw(pJuego->getRender(), 500, 75);
			std::cout << "0";
		}
		else{
			// escribit esto con texto pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
			Texto.loadTexto(pJuego->getRender(), std::to_string(pJuego->getBaul()->getCantidad(botones[activo]->getNombre())));
			Texto.draw(pJuego->getRender(), 500 , 75);
			std::cout << pJuego->getBaul()->getCantidad(botones[activo]->getNombre());
		}
	}

}

void Objetos3::update() {



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
