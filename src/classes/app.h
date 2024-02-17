#include <SDL2/SDL.h>

#ifndef APP_H
#define APP_H

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	TextBox* score;
} App;

#endif //APP_H
