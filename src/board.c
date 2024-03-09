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
	Board* new_board = (Board*) malloc(sizeof(Board));
	new_board->occupied_board_points = (PointOnBoard*) malloc(sizeof(PointOnBoard));
	new_board->occupied_board_points_size = 0;
	new_board->board_row_size = board_row_size;
	new_board->board_column_size = board_column_size;

	return new_board;
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
	for (int index = 0; index < board->occupied_board_points_size; index++) {
		PointOnBoard index_point = points[index];
		if (compare_points(index_point, point)) {
			return true;
		}
	}
	return false;
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

bool has_colitions_top(Piece* piece) {
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (INVISIBLE_BOARD > point.y) {
		return true;
	}
    }

    return false;
}

bool has_colitions_remains(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (has_point(board, point)) {
		return true;
	}
    }

    return false;
}

bool has_colitions_top_and_remains(Board* board, Piece* piece) {
	return has_colitions_top(piece) && has_colitions_remains(board, piece);
}

bool has_colitions_bottom_or_remains(Board* board, Piece* piece) {
    int board_row_size = board->board_row_size;
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (!(point.y < board_row_size) || has_point(board, point)) {
		return true;
	}
    }

    return false;
}

bool has_colitions_border_or_remains(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (!(0 <= point.x && point.x < board->board_column_size) || has_point(board, point)) {
		return true;
	}
    }

    return false;
}

bool has_colitions_border_left(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (!(0 <= point.x)) {
		return true;
	}
    }

    return false;
}

bool has_colitions_border_right(Board* board, Piece* piece) {
    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = piece->positions[i];
        if (!(point.x < board->board_column_size)) {
		return true;
	}
    }

    return false;
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
	unsigned int new_size = board->occupied_board_points_size - board->board_column_size;
	PointOnBoard* new_points = (PointOnBoard*) malloc(sizeof(PointOnBoard) * new_size);
	unsigned int current_new_point_index = 0;
	
	for (int index = 0; index < board->occupied_board_points_size; index++) {
		if (board->occupied_board_points[index].y != row) {
			new_points[current_new_point_index] = board->occupied_board_points[index];
			if (board->occupied_board_points[index].y < row) {
				new_points[current_new_point_index].y += 1;
			}
			current_new_point_index++;
		}
	}

	free(board->occupied_board_points);
	board->occupied_board_points = new_points;
	board->occupied_board_points_size = new_size;
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
