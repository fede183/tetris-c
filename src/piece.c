#include "stdio.h"
#include "stdbool.h"

#include "../classes/piece.h"
#include "../classes/point_on_board.h"
#include "../classes/config.h"
#include "../classes/color.h"
#include "color.c"
#include "random_number_generator.c"

Piece* createPiece() {

    Piece* newPiece = (Piece*) malloc(sizeof(Piece));

    unsigned int piece = random_number_generator(0, 7);
    unsigned int colorInt = random_number_generator(0, 7);
    enum point_color theColor = intToEnum(colorInt);

    const unsigned int figures[7][4] = {
        0, 2, 4, 6, //I
        1, 2, 3, 4, //Z
        0, 2, 3, 5, //S
        0, 2, 4, 5, //L
        1, 2, 3, 5, //T
        0, 1, 2, 3, //O
        1, 3, 4, 5, //J
    };

    for (unsigned int i = 0; i < 4; i++)
    {
        unsigned int figure_position = figures[piece][i]; 
        newPiece->positions[i].x = figure_position % 2;
        newPiece->positions[i].y = figure_position / 2;
        newPiece->positions[i].point_color = theColor;
    }

    return newPiece;
}

Piece* createPoint(PointOnBoard positions[4]) {
    Piece* newPiece = (Piece*) malloc(sizeof(Piece));
    for (unsigned int i = 0; i < 4; i++)
    {
        newPiece->positions[i] = positions[i];
    }
    return newPiece;
}

void copy(Piece* from, Piece* to) {
    for (unsigned int i = 0; i < 4; i++)
    {
        to->positions[i] = from->positions[i];
    }
}

PointOnBoard get_center_point(Piece* piece) {
    return piece->positions[1];
}

bool has_colitions_top(Piece* piece) {
    bool has_colitions_top = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        has_colitions_top = has_colitions_top || 
        !(0 <= piece->positions[i].y);
    }
    return has_colitions_top;
}
