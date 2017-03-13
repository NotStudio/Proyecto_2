#ifndef TEXTURASSDL_H
#define TEXTURASSDL_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Camara.h"
#include <vector>
#include "checkML.h"
using namespace std;

class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();

	bool load(SDL_Renderer* pRenderer, std::string const& nombreArch);
	size_t getAncho() { return tamTextura.ancho; }
	size_t getAlto() { return tamTextura.alto; }
	void draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame, Camara * Camera);

private:

	string nombreArc;

	struct tam {
		int ancho;
		int alto;
	} tamTextura;

	static SDL_Surface* loadSurface(string nombreArchivo) { //Método que carga la imagen en el surface. Para que funcione,  
															//debemos introducir la imagen en la carpeta del proyecto.
		SDL_Surface* pSurface = nullptr;


		pSurface = IMG_Load(nombreArchivo.c_str());



		if (pSurface == nullptr)
			cout << "Unable to load image " << nombreArchivo << "! \nSDL Error: " << SDL_GetError() << '\n';

		return pSurface;

	};

	SDL_Texture* pTexture;

};
struct Tilesheet
{
private:
	TexturasSDL* text;
	//el vector de rectangulos para dar las direcciones de los tiles en la textura
	vector<SDL_Rect*> Rects;
public:
	Tilesheet() { text = nullptr; }
	Tilesheet(size_t nRectangulos,TexturasSDL* t) {
		text = t;
		size_t width = t->getAncho(), height = t->getAlto();
		Rects.reserve(nRectangulos);
		int xp = 0, yp = 0;
		int h = sqrt((width * height)/nRectangulos),w = h;
		for (size_t i = 0; i < Rects.capacity(); i++)
		{
			Rects.push_back(new SDL_Rect{ xp,yp,w,h });
			xp += w;
			if (xp >= width) { xp = 0; yp += 128; }
		}
	};
	~Tilesheet() {
		for (size_t i = 0; i < Rects.size(); i++)
		{
			delete Rects[i];
			Rects[i] = nullptr;
		}
	}
	void load(SDL_Renderer* Render, string & dir) {
		text->load(Render, dir);
	};
	void draw(SDL_Renderer*Render, SDL_Rect & DstRect, int const &tipo, Camara*cam) {
		text->draw(Render, DstRect, Rects[tipo], cam);
	}

};

#endif