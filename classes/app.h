#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef APP_H
#define APP_H

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

#endif //APP_H
