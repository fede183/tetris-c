#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef BUTTON_H
#define BUTTON_H

typedef struct {
    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;

    bool pressed;
} button_t;

#endif //BUTTON_H
