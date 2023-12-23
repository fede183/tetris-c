#include "classes/text_box.h"

void _clean_text(TextBox* text_box) {
	SDL_FreeSurface(text_box->surface);
	SDL_DestroyTexture(text_box->message);
	free(text_box->font);
	free(text_box);
}

void init_text(SDL_Renderer* renderer, char* text, float w, float h, float x, float y) {
	TextBox* text_box = (TextBox*) malloc(sizeof(TextBox));
	
	SDL_Rect message_rect; 
	message_rect.x = x; 
	message_rect.y = y;
	message_rect.w = w;
	message_rect.h = h;

	text_box->rect = message_rect;

	text_box->font = TTF_OpenFont("../fonts/textFont.ttf", 24);
	if (text_box->font == NULL) {
		printf("Font load error");
		exit(0);
	}

	SDL_Color Black = {0, 0, 0};

	text_box->surface = TTF_RenderText_Solid(text_box->font, text, Black);

	if (text_box->surface == NULL) {
		printf("Surface load error: %s\n", SDL_GetError());
		exit(0);
	}

	text_box->message = SDL_CreateTextureFromSurface(renderer, text_box->surface);

	if (text_box->message == NULL) {
		printf("Texture load error: %s\n", SDL_GetError());
		exit(0);
	}
	if (SDL_QueryTexture(text_box->message, NULL, NULL, &text_box->rect.w, &text_box->rect.h) < 0) {
		printf("Query texture error: %s\n", SDL_GetError());
		exit(0);
	}
	if (SDL_RenderCopy(renderer, text_box->message, NULL, &text_box->rect) < 0) {
		printf("Render copy error: %s\n", SDL_GetError());
		exit(0);
	}
	_clean_text(text_box);
}

