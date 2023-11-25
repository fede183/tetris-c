#include <stdlib.h>

#include "linked_list.hpp"
#include "point_board.hpp"
#include "color.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP
struct Board
{
    struct LinkedList<LinkedList<PointForBoard>*>* board_rows;
    size_t board_row_size;
    size_t board_column_size;
};
#endif // BOARD_HPP