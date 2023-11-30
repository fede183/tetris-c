#include "stdlib.h"

#include "point_board.h"
#include "color.h"

#ifndef BOARD_H
#define BOARD_H
typedef struct
{
    PointForBoard** board_points;
    size_t board_row_size;
    size_t board_column_size;
} Board;
#endif // BOARD_H
