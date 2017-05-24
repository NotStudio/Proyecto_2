#include "Objetos3.h"
#include "checkML.h"


Objetos3::Objetos3(Juego* pJuego) : MenuJuego(pJuego)
{
	pJuego->reproducirEfecto("Multiusos");
	Fondo = pJuego->getTextura("HudCraft3", "idle");
	insertarBoton(Boton::ILUMINADO, 2, 5, mecanismo, "Mecanismo");
	insertarBoton(Boton::ILUMINADO, 2, 10, combustible, "Combustible");
	insertarBoton(Boton::ILUMINADO, 2, 15, fibraCarbono, "FibraCarbono");
	insertarBoton(Boton::ILUMINADO, 2, 20, moduloComandos, "ModuloComandos");
	insertarBoton(Boton::ILUMINADO, 2, 25, mensaje, "Eje");
	insertarBoton(Boton::ILUMINADO, 2, 30, mensaje, "Pantalla");
	//botones.emplace_back(new Boton(pJuego, "boton", 50, 200, mensaje, "ModuloComados"));
	insertarBoton(Boton::ILUMINADO, 2, 5, salir, "Salir");
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
}


void Objetos3::receta(std::string obj){
	TexturasSDL *T1 = nullptr, *T2 = nullptr, *T3 = nullptr;
	
	if (obj == "Mecanismo"){
		T1 = pJuego->getTextura("Engranajes", "idle");
		T2 = pJuego->getTextura("Eje", "idle");
		T3 = pJuego->getTextura("Fusible", "idle");
	}
	else if (obj == "Combustible"){
		T1 = pJuego->getTextura("Petroleo", "idle");
		T2 = pJuego->getTextura("Petroleo", "idle");
		T3 = pJuego->getTextura("Refinador", "idle");
	}

	else if (obj == "FibraCarbono"){
		T1 = pJuego->getTextura("Carbono", "idle");
		T2 = pJuego->getTextura("Madera", "idle");
		/*pJuego->getTextura("Madera", "idle")->draw(pJuego->getRender(), SDL_Rect{ 525, 260, 100, 100 }, nullptr, 0.0);*/
	}

	else if (obj == "ModuloComandos"){
		T1 = pJuego->getTextura("Pantalla", "idle");
		T2 = pJuego->getTextura("Circuito", "idle");
		T3 = pJuego->getTextura("Circuito", "idle");
	}
	if (T1)
		T1->draw(pJuego->getRender(), { fx * 50, fy * 20, 100, 100 });
	if (T2)
		T2->draw(pJuego->getRender(), { fx * 55, fy * 20, 100, 100 });
	if (T3)
		T3->draw(pJuego->getRender(), { fx * 60, fy * 20, 100, 100 });
}