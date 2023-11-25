#include "color.h"

#ifndef PIECE_H
#define PIECE_H
typedef struct Point
{
    int x, y;
    enum color point_color;
} Point;

typedef struct Piece
{
    struct Point positions[4];
} Piece;

#endif // PIECE_H
