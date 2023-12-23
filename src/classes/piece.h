#include "color.h"
#include "point_on_board.h"

#ifndef PIECE_H
#define PIECE_H
typedef struct Piece
{
    PointOnBoard positions[4];
} Piece;

#endif // PIECE_H
