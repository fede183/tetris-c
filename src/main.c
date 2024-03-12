#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "app.c"

int main(int argc, char *argv[])
{
	app = (App*) malloc(sizeof(App));

	init_SDL();

	while (!is_quit() && !check_game_over())
	{
		prepare_scene();
		present_scene();

		cycle();

		do_input();
	}

	if (!is_quit() && check_game_over()) {
		init_game_over();
	}

	while(!is_quit()) {
		prepare_scene();
		present_scene();

		prepare_game_over_scene();
		present_game_over_scene();
		
		do_input_game_over();
	}

	return 0;
}
