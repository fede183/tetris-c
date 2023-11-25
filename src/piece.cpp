#include <iterator>
#include <iostream>

#include "../classes/piece.hpp"
#include "../classes/config.hpp"
#include "../classes/color.hpp"
#include "random_number_generator.cpp"

Piece* createPiece() {

    Piece* newPiece = (Piece*) malloc(sizeof(Piece));

    unsigned int piece = random_number_generator(0, 7);
    unsigned int colorInt = random_number_generator(0, 7);
    color theColor = static_cast<color>(colorInt);

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

Piece* createPoint(Point positions[4]) {
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

Point get_center_point(Piece* piece) {
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