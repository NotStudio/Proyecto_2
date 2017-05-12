#include "MarcoHistorico.h"


MarcoHistorico::MarcoHistorico(Juego* pJuego) : MenuJuego(pJuego)
{
	Fondo = pJuego->getTextura("SelecMapaFondo", "idle");
	int contX = 0;
	int contY = 1;

	/*for (int i = 0; i < memorias->length(); i++)
	{
			botones.emplace_back(new Boton(pJuego, "button", contX * 170 + 20, contY * 50, salir, memorias[i]));
			contY++;
			if (contY == 6) {
				contY = 1;
				contX++;
			}
		}

	botones.emplace_back(new Boton(pJuego, "button", 565, 470, salir, "Salir"));
	Texto.LoadFuente(pJuego->getTipografia("Acme____", 30));
	imgObj = pJuego->getTextura(botones[activo]->getNombre(), "idle");*/

}


MarcoHistorico::~MarcoHistorico()
{
}


/*void Historia::salir(Juego* pJuego) {
	pJuego->popState();
}*/