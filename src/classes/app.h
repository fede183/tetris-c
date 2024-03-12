#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#ifndef APP_H
#define APP_H

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Renderer* game_over_renderer;
	SDL_Window* game_over_window;
	TextBox* score;
	TextBox* game_over_message;
	Mix_Music* music;
} App;

#endif //APP_H
