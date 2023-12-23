#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"

#ifndef BUTTON_H
#define BUTTON_H

typedef struct {
    SDL_Rect draw_rect;    // dimensions of button
    enum point_color color;
    bool pressed;
} Button;

#endif //BUTTON_H
