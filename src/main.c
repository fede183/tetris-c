#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "app.c"
/* #include "game.c" *1/ */

int main(int argc, char *argv[])
{
	app = (App*) malloc(sizeof(App));

	initSDL();

	atexit(cleanup);

	while (1)
	{
		prepareScene();

		doInput();

		presentScene();

		SDL_Delay(16);
	}


	return 0;
}
