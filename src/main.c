#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "app.c"

int main(int argc, char *argv[])
{
	App* app = init_SDL();

	while (!is_quit(app) && !check_game_over(app))
	{
		prepare_scene(app);
		present_scene(app);

		cycle(app);

		do_input(app);
	}

	if (!is_quit(app) && check_game_over(app)) {
		init_game_over(app);
	}

	while(!is_quit(app)) {
		prepare_scene(app);
		present_scene(app);

		prepare_game_over_scene(app);
		present_game_over_scene(app);
		
		do_input_game_over(app);
	}

	cleanup(app);

	return 0;
}
