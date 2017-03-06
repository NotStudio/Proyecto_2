#ifndef TEXTURASSDL_H
#define TEXTURASSDL_H
#include "SDL.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Camara.h"
using namespace std;

class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();

	bool load(SDL_Renderer* pRenderer, std::string const& nombreArch);

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

#endif