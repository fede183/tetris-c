#include <stdio.h>
#include <stdbool.h>  

#include "classes/board.h"
#include "classes/point_on_board.h"
#include "piece.c"

bool equal(const PointOnBoard* point1, const PointOnBoard* point2)
{
	return point1->x == point2->x;
}

Board* create_board(const unsigned int board_row_size, const unsigned int board_column_size) {
	Board* newBoard = (Board*) malloc(sizeof(Board));
	newBoard->occupied_board_points = (PointOnBoard*) malloc(sizeof(PointOnBoard));
	newBoard->occupied_board_points_size = 0;
	newBoard->board_row_size = board_row_size;
	newBoard->board_column_size = board_column_size;

	return newBoard;
}

void clean_board(Board* board) {
    free(board->occupied_board_points);
    free(board);
}

static bool compare_points(PointOnBoard elem1, PointOnBoard elem2) {
    return elem1.x == elem2.x && elem1.y == elem2.y;
}

bool has_point(Board* board, PointOnBoard point) {
	PointOnBoard* points = board->occupied_board_points;
	bool it_exists = false;
	for (int index = 0; index < board->occupied_board_points_size; index++) {
		PointOnBoard index_point = points[index];
		it_exists = it_exists || compare_points(index_point, point);
	}
	return it_exists;
}

void add_point(Board* board, PointOnBoard new_point) {
	if (has_point(board, new_point)) {
		return;	
	}

	PointOnBoard* new_points = (PointOnBoard*) malloc(sizeof(PointOnBoard) * (board->occupied_board_points_size + 1));

	for (int index = 0; index < board->occupied_board_points_size; index++) {
		new_points[index] = board->occupied_board_points[index];
	}

	new_points[board->occupied_board_points_size] = new_point;
    	free(board->occupied_board_points);

	board->occupied_board_points = new_points;	
	board->occupied_board_points_size += 1;
}

void add_piece(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++) {
        add_point(board, piece->positions[i]);
    }
}

bool has_colitions_bottom_or_remains(Board* board, Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = board->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        has_colitions_top = has_colitions_top || 
        !(point.y < board_row_size) || has_point(board, point);
    }

    return has_colitions_top;
}

bool has_colitions_bottom_and_top(Board* board, Piece* piece) {
    bool has_colitions_top = false;
    int board_row_size = board->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        has_colitions_top = has_colitions_top || 
        (board_row_size <= point.y || has_point(board, point));
    }

    return has_colitions_top;
}

bool has_colitions_border_or_remains(Board* board, Piece* piece) {
    bool has_colitions_border_or_remains = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        has_colitions_border_or_remains = has_colitions_border_or_remains || 
        !(0 <= point.x && point.x < board->board_column_size) 
        || has_point(board, point);
    }

    return has_colitions_border_or_remains;
}

bool has_colitions_border_left(Board* board, Piece* piece) {
    bool has_colitions_border_left = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        has_colitions_border_left = has_colitions_border_left || 
        !(0 <= point.x);
    }

    return has_colitions_border_left;
}

bool has_colitions_border_right(Board* board, Piece* piece) {
    bool has_colitions_border_right = false;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        has_colitions_border_right = has_colitions_border_right || 
        !(point.x < board->board_column_size);
    }

    return has_colitions_border_right;
}

bool delete_line_if_complete(Board* board, unsigned int row) {
	bool is_row_complete = true;
	for (int column = 0; column < board->board_column_size; column++) {
		PointOnBoard current_point;
		current_point.y = row;
		current_point.x = column;
		if (!has_point(board, current_point)) {
			return false;
		}
	}

	PointOnBoard* new_points = (PointOnBoard*) malloc(sizeof(PointOnBoard) * (board->occupied_board_points_size - board->board_column_size));
	
	for (int index = 0; index < board->occupied_board_points_size; index++) {
		if (board->occupied_board_points[index].y != row) {
			PointOnBoard point = board->occupied_board_points[index];
			new_points[index] = point;
		}
		if (board->occupied_board_points[index].y > row) {
			new_points[index].y += 1;
		}
	}

	free(board->occupied_board_points);
	board->occupied_board_points = new_points;
	board->occupied_board_points_size = board->occupied_board_points_size - board->board_column_size;
	return true;
}

unsigned int delete_all_complete_lines(Board* board) {
	unsigned int quantity_delete_lines = 0;
    	unsigned int row_size = board->board_row_size;

	for (int row = 0; row < row_size; row++) {
		if (delete_line_if_complete(board, row)) {
			quantity_delete_lines++;
		}
	}    

	return quantity_delete_lines;
}

unsigned int get_row_quantity(Board* board) {
    return board->board_row_size;
}

unsigned int get_column_quantity(Board* board, const unsigned int index) {
    return board->board_column_size;
}
