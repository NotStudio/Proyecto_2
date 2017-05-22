#include "MenuJuego.h"

MenuJuego::MenuJuego(Juego* juego):EstadoPG(juego)
{
	MenuState_ = STARTING;
	kek.LoadFuente(pJuego->getTipografia("ethnocen"));
	ayuda.LoadFuente(pJuego->getTipografia("a"));
	ayuda.loadTexto(pJuego->getRender(), "Press H",200, { 255,255,255,50 });
}


MenuJuego::~MenuJuego()
{
	for (auto b : botones) {
		delete b;
		b = nullptr;
	}
}

void MenuJuego::update() {
	updateBotones();
	if (!MenuState_)
		alpha++;
	if (alpha == 255)
		MenuState_ = STARTED;

}
void MenuJuego::draw() {
	if(Fondo!=nullptr)
		Fondo->draw(pJuego->getRender(), { 0,0,pJuego->window.ancho,pJuego->window.alto }, nullptr);
	
	for (int i = 0; i < botones.size(); i++)
	{
		botones[i]->draw();
	}
	ayuda.draw(pJuego->getRender(), 0, 0);
	if (kek.IsCharged())
		kek.draw(pJuego->getRender(), 0, 0);

}

void MenuJuego::handleEvent(const SDL_Event & event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_H:
			if (!kek.IsCharged())
				kek.loadTexto(pJuego->getRender(), botones[activo]->getDescripcion());
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_DOWN:
			if (activo < botones.size() - 1) {
				pJuego->reproducirEfecto("Menu");
				activo++;
			}
			break;
		case SDL_SCANCODE_UP:
			if (activo > 0) {
				pJuego->reproducirEfecto("Menu");
				activo--;
			}
			break;
		case SDL_SCANCODE_RETURN:{
									 pJuego->reproducirEfecto("Click");
									 botones[activo]->accion();
									
									 break;
		}
		case SDL_SCANCODE_H:
			if (kek.IsCharged())
				kek.liberar();
			break;
		default:
			break;
		}
	case SDL_MOUSEMOTION:
		if (botones.size() > 0) {
			int i = botones.size() - 1;
			while (i >= 0 && !botones[i]->Dentro(event.motion.x, event.motion.y))
			{
				i--;
			}
			if (i > -1 && activo != i) {
				pJuego->reproducirEfecto("Menu");
				activo = i;
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (botones[activo]->Dentro(event.button.x, event.button.y))
				pJuego->reproducirEfecto("Click");
				botones[activo]->accion();
		}
		break;
		
	default:
		break;
	}
}

void MenuJuego::updateBotones()
{
	for (size_t i = 0; i < botones.size(); i++)
	{
		if (i == activo) {
			botones[i]->aumentar();
		}
		else
		{
			botones[i]->normal();
		}
		botones[i]->update();
	}
}
