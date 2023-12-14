#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <callback.h>

#include "button.c"
#include "game.c"
#include "../classes/app.h"
#include "../classes/config.h"

App* app;

void cleanup();
void init_SDL();
void handle_input(SDL_Keycode);
void do_input();
void prepare_scene();
void present_scene();

void init_SDL(void)
{
	atexit(cleanup);

	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app->window = SDL_CreateWindow("Tetris C", 
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       display_width + display_side_block_width, display_heigth, windowFlags);

	if (!app->window)
	{
		printf("Failed to open %d x %d window: %s\n", display_width + display_side_block_width, display_heigth, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

	if (!app->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void cleanup() {
	SDL_Quit();
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	free(app);
}

void handle_input(SDL_Keycode code) {
	if (code == SDLK_ESCAPE || code == SDLK_q) {
		exit(0);
	}
}

void do_input(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				handle_input(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}
}

void prepare_scene(void)
{
	SDL_SetRenderDrawColor(app->renderer, 96, 128, 12, 255);
	SDL_RenderClear(app->renderer);
}

void present_scene(void)
{
	SDL_RenderPresent(app->renderer);
}

