#include "board.h"
#include "piece.h"
#include "config.h"

#ifndef GAME_H
#define GAME_H
struct Game
{
    struct Board* board;
    Piece* piece;
    Piece* backout_piece;
    Piece* next_piece;
    unsigned int score, level, complete_lines;
};
#endif // GAME_H
