#include "piece.hpp"
#include "color.hpp"

#ifndef POINT_BOARD_H
#define POINT_BOARD_H

typedef struct PointForBoard
{
    int x;
    enum color point_color;
} PointForBoard;

#endif // POINT_BOARD_H