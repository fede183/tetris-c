#include "color.hpp"

#ifndef PIECE_HPP
#define PIECE_HPP
typedef struct Point
{
    int x, y;
    enum color point_color;
} Point;

typedef struct Piece
{
    struct Point positions[4];
} Piece;

#endif // PIECE_HPP