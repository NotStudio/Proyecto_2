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

	//tamTextura.alto = pSurface->clip_rect.h;
	//tamTextura.ancho = pSurface->clip_rect.w;

	nombreArc = nombreArch;
	SDL_DestroyTexture(pTexture);


	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);


	SDL_FreeSurface(pSurface);

	return success = pTexture != nullptr;

};

void TexturasSDL::draw(SDL_Renderer* pRenderer, SDL_Rect const& rect, SDL_Rect* const& frame, double angle , SDL_Point* center, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(pRenderer, pTexture, frame, &rect,angle,center,flip);
}
void TexturasSDL::draw(SDL_Renderer * pRenderer, SDL_Rect const & rect, SDL_Rect * const & frame, Camara Camera)
{

	SDL_Point kek = { 200,200 };
	kek.x -= rect.x;
	kek.y -= rect.y;
	SDL_RenderCopyEx(pRenderer, pTexture, frame, &rect, Camera.getAngulo(),&kek , SDL_FLIP_NONE);
}
