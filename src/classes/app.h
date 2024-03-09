#include <SDL2/SDL.h>

#ifndef APP_H
#define APP_H

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Renderer* game_over_renderer;
	SDL_Window* game_over_window;
	TextBox* score;
	TextBox* game_over_message;
} App;

#endif //APP_H
