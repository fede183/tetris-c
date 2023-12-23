#include <SDL2/SDL.h>
#include "../classes/button.h"


Button* create_button(int x, int y, int w, int h, enum point_color color) {
	Button* button = (Button*) malloc(sizeof(Button));
	button->draw_rect.x = x;
	button->draw_rect.y = y;
	button->draw_rect.w = w;
	button->draw_rect.h = h;
	button->color = color;
	button->pressed = false;
}

static void button_process_event(Button *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if (ev->type == SDL_MOUSEBUTTONDOWN) {
        if (ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= btn->draw_rect.x &&
                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
                ev->button.y >= btn->draw_rect.y &&
                ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}

