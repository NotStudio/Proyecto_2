#include "TexturasSDL.h"



TexturasSDL::TexturasSDL()
{
	pTexture = nullptr;
}


TexturasSDL::~TexturasSDL()
{
	pTexture = nullptr;


}


bool TexturasSDL::load(SDL_Renderer* pRenderer, std::string const& nombreArch) {
	bool success = true;

	
	SDL_Surface* pSurface = loadSurface(nombreArch);

	tamTextura.alto = pSurface->clip_rect.h;
	tamTextura.ancho = pSurface->clip_rect.w;

	nombreArc = nombreArch;
	SDL_DestroyTexture(pTexture);


	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);


	SDL_FreeSurface(pSurface);

	return success = pTexture != nullptr;

};

void TexturasSDL::draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame ) {

	SDL_RenderCopy(pRenderer, pTexture, frame, &rect);

};

