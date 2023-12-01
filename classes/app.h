#include <SDL2/SDL.h>
#include <SDL2/SDL_tff.h>

#ifndef APP_H
#define APP_H

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Window *lost_message;
	TTF_Font* font;
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
	/* Mix_Music* music; */
} App;

#endif //APP_H
