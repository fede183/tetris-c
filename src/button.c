#include <SDL2/SDL.h>
#include "../classes/button.h"


static void button_process_event(button_t *btn, const SDL_Event *ev) {
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

