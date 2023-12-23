#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef TEXT_BOX_H
#define TEXT_BOX_H

typedef struct {
	SDL_Surface* surface;
	SDL_Texture* message;
	TTF_Font* font;
	SDL_Rect rect;
} TextBox;

#endif //TEXT_BOX_H
