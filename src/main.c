#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "app.c"

int main(int argc, char *argv[])
{
	app = (App*) malloc(sizeof(App));

	init_SDL();

	while (!is_quit())
	{
		prepare_scene();

		present_scene();

		do_input();

		SDL_Delay(16);
	}


	return 0;
}
