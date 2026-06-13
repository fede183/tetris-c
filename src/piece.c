#include "stdio.h"
#include "stdbool.h"

#include "classes/piece.h"
#include "classes/point_on_board.h"
#include "classes/config.h"
#include "classes/color.h"
#include "color.c"
#include "random_number_generator.c"

unsigned int FIGURES[7][4][2] = {
	{{1, 0}, {1, 1}, {2, 0}, {2, 1}}, //O
	{{0, 1}, {1, 1}, {2, 1}, {3, 1}}, //I
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, //Z
	{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, //S
	{{0, 0}, {1, 0}, {2, 0}, {0, 1}}, //L
	{{0, 0}, {1, 0}, {2, 0}, {1, 1}}, //T
	{{0, 0}, {1, 0}, {2, 0}, {2, 1}}, //J
};

CenterPoint getCenterPointCoordinates(int value) {
	switch(value) {
		case 0:
			return (CenterPoint) { .x = 2.0, .y = 1.0 };
		case 1:
			return (CenterPoint) { .x = 2.0, .y = 2.0 };
		default:
			return (CenterPoint) { .x = 1.5, .y = 1.5 };
	
	}
}

Piece* create_piece() {

    Piece* new_piece = (Piece*) malloc(sizeof(Piece));

    unsigned int piece = random_number_generator(0, 7);
    unsigned int color_int = random_number_generator(0, 7);

    enum point_color the_color = intToEnum(color_int);

    for (unsigned int i = 0; i < 4; i++)
    {
        new_piece->positions[i].x = FIGURES[piece][i][0];
        new_piece->positions[i].y = FIGURES[piece][i][1];
        new_piece->positions[i].point_color = the_color;
    }

    new_piece->center_point = getCenterPointCoordinates(piece);

    return new_piece;
}

void copy(Piece* from, Piece* to) {
    for (unsigned int i = 0; i < 4; i++)
    {
        to->positions[i] = from->positions[i];
    }
    to->center_point = from->center_point;
}
