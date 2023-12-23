#include "board.h"
#include "piece.h"

#ifndef GAME_H
#define GAME_H
typedef struct
{
    Board* board;
    Piece* piece;
    Piece* next_piece;
    unsigned int score, level, complete_lines;
} Game;
#endif // GAME_H
