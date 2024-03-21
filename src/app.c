#include <stdbool.h>  
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <callback.h>

#include "text_box.c"
#include "rectagle.c"
#include "game.c"
#include "classes/app.h"
#include "classes/config.h"

App* app;
Game* game;
bool quit;

SDL_Color SDLColors[8] = {BLUE_COLOR, VIOLET_COLOR, RED_COLOR, GREEN_COLOR, YELLOW_COLOR, LIGHT_BLUE_COLOR, ORANGE_COLOR, MEDIUM_BLUE_COLOR};
int rendererFlags = SDL_RENDERER_ACCELERATED;
int windowFlags = 0;

void cleanup();
void init_SDL();
void handle_input(SDL_Keycode);
void do_input();
void prepare_scene();
void present_scene();
void draw_game_state();
void draw_piece();
void draw_occupied_points();
void draw_point();
bool check_game_over();

void init_SDL(void)
{
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

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) == -1) {
		printf("Failed to create audio: %s\n", SDL_GetError());
		exit(1);
	}

	app->music = Mix_LoadMUS(MUSIC_FILE);

	if (!app->music)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_PlayMusic(app->music, -1) == -1) {
		printf("Failed to play music: %s\n", SDL_GetError());
		exit(1);
        }

	app->score = init_text(DISPLAY_SCORE_WIGTH, DISPLAY_SCORE_HEIGTH, DISPLAY_SCORE_X, DISPLAY_SCORE_Y);

	game = init_game();
	quit = false;
}

bool is_quit() {
	return quit;
}

void cleanup() {
	if (app->score) {
		free(app->score);
	}
	if (app->renderer) {
		SDL_DestroyRenderer(app->renderer);
	}
	if (app->window) {
		SDL_DestroyWindow(app->window);
	}
	if (app->music) {
		Mix_FreeMusic(app->music);
    		Mix_CloseAudio();
	}

	if (check_game_over()) {
		free(app->game_over_message);
		SDL_DestroyRenderer(app->game_over_renderer);
		SDL_DestroyWindow(app->game_over_window);
	}

	free(app);
	clean_game(game);
	TTF_Quit();
	SDL_Quit();
	quit = true;
}

void prepare_scene(void)
{
	SDL_Color background_color = GREY_COLOR;
	SDL_SetRenderDrawColor(app->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
	SDL_RenderClear(app->renderer);
}

void present_scene(void)
{
	char score_text[10];
	sprintf(score_text, "Score: %d", game->score);
	show_text(app->score, app->renderer, score_text);

	init_rectagle(app->renderer, DISPLAY_BOARD_WIDTH, DISPLAY_BOARD_HEIGTH, DISPLAY_BOARD_X, DISPLAY_BOARD_Y, (SDL_Color) BLACK_COLOR);
	init_rectagle(app->renderer, DISPLAY_NEXT_PIECE_BLOCK_WIDTH, DISPLAY_NEXT_PIECE_BLOCK_HEIGTH, DISPLAY_NEXT_PIECE_BLOCK_POSITION_X, DISPLAY_NEXT_PIECE_BLOCK_POSITION_Y, (SDL_Color) BLACK_COLOR);

	draw_game_state(game->piece);
	SDL_RenderPresent(app->renderer);
}

void draw_game_state() {
	Piece* piece = game->piece;
	Piece* next_piece = game->next_piece;
	Piece* next_piece_copy = (Piece*) malloc(sizeof(Piece));
	copy(next_piece, next_piece_copy);
	
	for (unsigned int i = 0; i<4; i++) {
		PointOnBoard point = next_piece_copy->positions[i];
		point.y = point.y + NEXT_PIECE_BLOCK_Y + 1;
		point.x = point.x + NEXT_PIECE_BLOCK_X + 1;
		draw_point(point);
	}
	
	draw_piece(piece);
	draw_piece(next_piece_copy);
	draw_occupied_points();
	free(next_piece_copy);
}

void draw_piece(Piece* piece) {
	for (unsigned int i = 0; i<4; i++) {
		PointOnBoard point = piece->positions[i];
		draw_point(point);
	}
}

void draw_occupied_points() {
	PointOnBoard* points = game->board->occupied_board_points;
	unsigned int points_size = game->board->occupied_board_points_size;

	for (unsigned int i = 0; i<points_size; i++) {
		PointOnBoard point = points[i];
		draw_point(point);
	}
}

void draw_point(PointOnBoard point) {
	unsigned int display_x = SQUARE_SIZE*(point.x + 1);
	unsigned int display_y = SQUARE_SIZE*(point.y+HEADER);

	if (point.y < INVISIBLE_BOARD) {
		return;
	}

	init_rectagle(app->renderer, SQUARE_SIZE, SQUARE_SIZE, display_x, display_y, SDLColors[point.point_color]);
}

void handle_input(SDL_Keycode code) {
	if (code == SDLK_ESCAPE || code == SDLK_q) {
		cleanup();
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
				cleanup();
				break;
			case SDL_KEYDOWN:
				handle_input(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}
}

void cycle() {
	descend(game);
	SDL_Delay(100);
}

// Game Over Window
bool check_game_over() {
	return is_game_over(game);
}

void init_game_over() {
	app->game_over_window = SDL_CreateWindow("Game Over", 
                                       0,
                                       0,
                                       GAME_OVER_DISPLAY_WIDTH, GAME_OVER_DISPLAY_HEIGTH, windowFlags);

	if (!app->game_over_window)
	{
		printf("Failed to open %d x %d window: %s\n", GAME_OVER_DISPLAY_WIDTH, GAME_OVER_DISPLAY_HEIGTH, SDL_GetError());
		exit(1);
	}

	app->game_over_renderer = SDL_CreateRenderer(app->game_over_window, -1, rendererFlags);

	if (!app->game_over_renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	app->game_over_message = init_text(DISPLAY_GAME_OVER_MESSAGE_WIGTH, DISPLAY_GAME_OVER_MESSAGE_HEIGTH, DISPLAY_GAME_OVER_MESSAGE_X, DISPLAY_GAME_OVER_MESSAGE_Y);
}

void prepare_game_over_scene(void)
{
	SDL_Color background_color = RED_COLOR;
	SDL_SetRenderDrawColor(app->game_over_renderer, background_color.r, background_color.g, background_color.b, background_color.a);
	SDL_RenderClear(app->game_over_renderer);
}

void present_game_over_scene(void)
{
	char* game_over_text = "Game Over! Press q or Esc to quit";
	show_text(app->game_over_message, app->game_over_renderer, game_over_text);

	SDL_RenderPresent(app->game_over_renderer);
}

void handle_input_game_over(SDL_Keycode code) {
	if (code == SDLK_ESCAPE || code == SDLK_q) {
		cleanup();
	}
}

void do_input_game_over(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				cleanup();
				break;
			case SDL_KEYDOWN:
				handle_input_game_over(event.key.keysym.sym);
				break;
			default:
				break;
		}
	}
}
