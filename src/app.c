#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <callback.h>

#include "button.c"
#include "text_box.c"
#include "rectagle.c"
#include "game.c"
#include "../classes/app.h"
#include "../classes/config.h"

App* app;
Game* game;

void cleanup();
void init_SDL();
void handle_input(SDL_Keycode);
void do_input();
void prepare_scene();
void present_scene();
void draw_game_state();
void draw_piece();

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

	if (TTF_Init() < 0) {
		printf("Couldn't initialize TTF: %s\n", SDL_GetError());
		exit(1);
	}

	app->window = SDL_CreateWindow("Tetris C", 
                                       0,
                                       0,
                                       display_width, display_heigth, windowFlags);

	if (!app->window)
	{
		printf("Failed to open %d x %d window: %s\n", display_width, display_heigth, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

	if (!app->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	game = init_game(); 
}

void cleanup() {
	TTF_Quit();
	SDL_Quit();
	if (!app->renderer) {
		SDL_DestroyRenderer(app->renderer);
	}
	if (!app->window) {
		SDL_DestroyWindow(app->window);
	}
	free(app);
	free(game);
}

void handle_input(SDL_Keycode code) {
	if (code == SDLK_ESCAPE || code == SDLK_q) {
		exit(0);
	}
	else if (code == SDLK_LEFT) {
		move_left(game);
	}
	else if (code == SDLK_RIGHT) {
		move_right(game);
	}
	else if (code == SDLK_DOWN) {
		descend(game);
	}
	else if (code == SDLK_SPACE) {
		rotate(game);
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
	SDL_SetRenderDrawColor(app->renderer, 128, 128, 128, 10);
	SDL_RenderClear(app->renderer);
}

void present_scene(void)
{
	init_text(app->renderer, "Score", display_score_wigth, display_score_heigth, display_score_x, display_score_y);
	init_rectagle(app->renderer, display_board_width, display_board_heigth, display_board_x, display_board_y, (SDL_Color) black_color);
	init_rectagle(app->renderer, display_next_piece_block_width, display_next_piece_block_heigth, display_next_piece_block_position_x, display_next_piece_block_position_y, (SDL_Color) black_color);

	draw_game_state(game->piece);
	SDL_RenderPresent(app->renderer);
}

void draw_game_state() {
	draw_piece();
}

void draw_piece() {
	Piece* piece = game->piece;
	for (unsigned int i = 0; i<4; i++) {
		PointOnBoard point = piece->positions[i];
		init_rectagle(app->renderer, square_size, square_size, square_size*point.x, square_size*point.y, (SDL_Color) red_color);
	}
}
