#include "stdlib.h"
#include "point_on_board.h"

#ifndef BOARD_H
#define BOARD_H
typedef struct
{
    PointOnBoard* occupied_board_points;
    size_t occupied_board_points_size;
    size_t board_row_size;
    size_t board_column_size;
} Board;
#endif // BOARD_H
