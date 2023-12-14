#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "app.c"
/* #include "game.c" *1/ */

int main(int argc, char *argv[])
{
	app = (App*) malloc(sizeof(App));

	init_SDL();

	atexit(cleanup);

	while (1)
	{
		prepare_scene();

		do_input();

		present_scene();

		SDL_Delay(16);
	}


	return 0;
}
