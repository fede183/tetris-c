#include <SDL2/SDL.h>


void init_rectagle(SDL_Renderer* renderer, float w, float h, float x, float y) {
	
	SDL_Rect rect; 
	rect.x = x; 
	rect.y = y;
	rect.w = w;
	rect.h = h;

    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    	SDL_RenderDrawRect(renderer, &rect);
}

