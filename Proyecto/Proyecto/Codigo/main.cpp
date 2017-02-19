#include <SDL.h>
#include <Box2D\Box2D.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>  // la consola: cin / cout
using namespace std; // Para cualificar automaticamente con std:: los identificadores de la librería estandar 
					 //----------------------------------------------------------------------------------------------------------------------

					 // declaraciones globales

bool init(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);  // arranca SDL y define las variables: pWindow y pRenderer

bool loadTexture(SDL_Renderer* pRenderer, SDL_Texture* & pTexture);  // crea una textura a partir de un archivo y define la variable pTexture 

void close(SDL_Window* & pWindow, SDL_Renderer* & pRenderer);  // libera los recursos y apaga SDL

void render(SDL_Renderer* pRenderer, SDL_Texture* pTexture);  // dibuja la textura 

bool handle_events();

void update();

const int SCREEN_WIDTH = 640;   //Screen dimension
const int SCREEN_HEIGHT = 480;  //Screen dimension

								//----------------------------------------------------------------------------------------------------------------------

int main(int argc, char* args[]) {  // SDL require esta cabecera 
									//system("chcp 1252");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	SDL_Window * pWin = nullptr;        //The window we'll be rendering to
	SDL_Renderer * pRender = nullptr;   //The renderer by the window  
	SDL_Texture *pTexture = nullptr;    //The image we will load and show on the screen

										//Start up SDL and create resources
	init(pWin, pRender);

	loadTexture(pRender, pTexture);

	if (pWin == nullptr || pRender == nullptr || pTexture == nullptr) {
		cout << " Fatal Error\n Press Enter";  cin.ignore();   //system("pause");
	}
	else {
		bool exit = false;

		render(pRender, pTexture);  //  Show the texture
		exit = handle_events();	    //  
		while (!exit) {    // While application is running
			update();
			// SDL_Delay(2000);  //Wait two seconds
			render(pRender, pTexture);
			exit = handle_events();
		}
	}

	// free resources and close SDL
	SDL_DestroyTexture(pTexture);
	pTexture = nullptr;

	close(pWin, pRender);

	return 0;
}
//----------------------------------------------------------------------------------------------------------------------

bool init(SDL_Window* &pWindow, SDL_Renderer* &pRenderer) {

	bool success = true; //Initialization flag

						 //Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWindow = SDL_CreateWindow("SDL Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (pWindow == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRenderer == nullptr) {
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	return success;
}
//----------------------------------------------------------------------------------------------------------------------

bool loadTexture(SDL_Renderer * pRenderer, SDL_Texture* & pTexture) {
	//The image we will load 
	char bmpName[]{ "..\\bmps\\hello_world.bmp" };
	//std::string bmpName{ "..\\bmps\\hello_world.bmp"};

	SDL_Surface* pTempSurface = nullptr;
	bool success = true;  //Loading success flag

						  //Load image
	pTempSurface = SDL_LoadBMP(bmpName);  // si usamos string: bmpName.c_str() 
	if (pTempSurface == nullptr) {
		cout << "Unable to load image " << bmpName << "! \nSDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
		SDL_FreeSurface(pTempSurface);
		success = pTexture != nullptr;
	}

	return success;
}
//----------------------------------------------------------------------------------------------------------------------

void close(SDL_Window* & pWindow, SDL_Renderer* & pRenderer) {

	SDL_DestroyRenderer(pRenderer);
	pRenderer = nullptr;

	SDL_DestroyWindow(pWindow);
	pWindow = nullptr;

	SDL_Quit();
}
//----------------------------------------------------------------------------------------------------------------------

void render(SDL_Renderer* pRenderer, SDL_Texture* pTexture) {

	//Clear the window to background color 
	SDL_RenderClear(pRenderer);

	// Draw objets 
	SDL_RenderCopy(pRenderer, pTexture, nullptr, nullptr);  // nullptr, nullptr -> toda la textura en toda la ventana

															//Show the window
	SDL_RenderPresent(pRenderer);
}
//----------------------------------------------------------------------------------------------------------------------

bool handle_events() {
	SDL_Event e;
	bool running = true;
	//Handle events on queue
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)  //User requests quit
			running = false;
		// else if(...)   // ...
	}
	return !running;
}
//----------------------------------------------------------------------------------------------------------------------

void update() {
	// update objects
}
//----------------------------------------------------------------------------------------------------------------------

