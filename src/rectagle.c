#include <SDL2/SDL.h>
#include "classes/color.h"

void init_rectagle(SDL_Renderer* renderer, float w, float h, float x, float y, SDL_Color color) {
	
	SDL_Rect rect; 
	rect.x = x; 
	rect.y = y;
	rect.w = w;
	rect.h = h;

    	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
}

