#ifndef TEXTURASSDL_H
#define TEXTURASSDL_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Camara.h"
#include <vector>
#include "checkML.h"
#include <SDL_ttf.h>
using namespace std;

class TexturasSDL
{
public:
	TexturasSDL();
	virtual ~TexturasSDL();

	bool load(SDL_Renderer* pRenderer, std::string const& nombreArch);
	size_t getAncho() { return tamTextura.ancho; }
	size_t getAlto() { return tamTextura.alto; }
	string getNombreArchivo();
	virtual void draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame, Camara * Camera, bool FlipHorinzontal = false);

protected:
	void liberar() {
		if (pTexture != nullptr) {
			SDL_DestroyTexture(pTexture);
			pTexture = nullptr;
		}
	};
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
//Struct de Fuente, que es para cargar una fuente
struct Fuente
{
	Fuente() { fuente = nullptr; }
	void loadFuente(string const & dir, int const  tam = 50) {
		fuente = TTF_OpenFont(dir.c_str(), tam);
		if (fuente == nullptr) {
			cout << "No se ha cargado la fuente \n";
		}
		else {
			fichero = dir;
			tamFuente = tam;
		}
	}
	~Fuente() {
		TTF_CloseFont(fuente);
		fuente = nullptr;
	}
	TTF_Font * fuente;
	int tamFuente;
	string fichero;
};
class TextoSDL : public TexturasSDL
{
public:
	TextoSDL() :TexturasSDL() { font = nullptr; }
	void LoadFuente(Fuente * fuente ) {
		font = fuente;
	}
	//funcion para meter un texto en la textura
	void loadTexto(SDL_Renderer * pRender ,string const txto,SDL_Color const  color = {0,0,0}) {
		liberar();
		SDL_Surface* surfaceText = TTF_RenderText_Blended(font->fuente, txto.c_str(), color);
		if (surfaceText == nullptr)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			texto = txto;
			pTexture = SDL_CreateTextureFromSurface(pRender, surfaceText);
			if (pTexture == nullptr) {
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else {
				rct = surfaceText->clip_rect;
				tamTextura.ancho = rct.w;
				tamTextura.alto = rct.h;
			}
			SDL_FreeSurface(surfaceText);
		}
	}
	void cambiarColor(SDL_Color const _color, SDL_Renderer * pRender){
		loadTexto(pRender, texto, _color);
	}
	//para dibujar el texto
	virtual void draw(SDL_Renderer* pRenderer, int x , int y) {
		SDL_Rect rect = { x,y,tamTextura.ancho,tamTextura.alto };
		SDL_RenderCopyEx(pRenderer, pTexture, &rct, &rect, 0, NULL, SDL_FLIP_NONE);
	}
private:
	SDL_Rect rct;
	Fuente * font;
	string texto;
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