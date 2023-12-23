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
#include "classes/app.h"
#include "classes/config.h"

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
                                       DISPLAY_WIDTH, DISPLAY_HEIGTH, windowFlags);

	if (!app->window)
	{
		printf("Failed to open %d x %d window: %s\n", DISPLAY_WIDTH, DISPLAY_HEIGTH, SDL_GetError());
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
	init_text(app->renderer, "Score", DISPLAY_SCORE_WIGTH, DISPLAY_SCORE_HEIGTH, DISPLAY_SCORE_X, DISPLAY_SCORE_Y);
	init_rectagle(app->renderer, DISPLAY_BOARD_WIDTH, DISPLAY_BOARD_HEIGTH, DISPLAY_BOARD_X, DISPLAY_BOARD_Y, (SDL_Color) BLACK_COLOR);
	init_rectagle(app->renderer, DISPLAY_NEXT_PIECE_BLOCK_WIDTH, DISPLAY_NEXT_PIECE_BLOCK_HEIGTH, DISPLAY_NEXT_PIECE_BLOCK_POSITION_X, DISPLAY_NEXT_PIECE_BLOCK_POSITION_Y, (SDL_Color) BLACK_COLOR);

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
		unsigned int display_x = SQUARE_SIZE*(point.x + 1);
		unsigned int display_y = SQUARE_SIZE*(point.y+HEADER);

		if (point.y < INVISIBLE_BOARD) {
			continue;
		}

		init_rectagle(app->renderer, SQUARE_SIZE, SQUARE_SIZE, display_x, display_y, (SDL_Color) RED_COLOR);
	}
}
