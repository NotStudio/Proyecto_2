#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Juego.h"
#include <exception>
#include <string>
#include <time.h>
using namespace std;

void showMessage(const std::string & msg) {
	char const *s = msg.c_str();

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		"ERROR", s, nullptr);

};

int main(int argc, char* args[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	srand(time(NULL));

	b2Vec2 gravity(0.0f, 0.0f);

	b2World world(gravity);
	
	Juego juego(&world);
	
//	system("PAUSE");

	return 0;
}
