#include "color.h"
#include "point_on_board.h"

#ifndef PIECE_H
#define PIECE_H

enum piece_type { 
	I = 0, 
	Z = 1, 
	S = 2, 
	L = 3, 
	T = 4, 
	O = 5, 
	J = 6,
};

typedef struct CenterPoint 
{
	float x, y;
} CenterPoint;

typedef struct Piece
{
    PointOnBoard positions[4];
    CenterPoint center_point;
} Piece;

#endif // PIECE_H
