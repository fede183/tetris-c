#include "classes/config.h"
#include "classes/piece.h"
#include "classes/game.h"
#include "board.c"

Game* init_game() {
    Game* new_game = (Game*) malloc(sizeof(Game));
    // Declare Game
    new_game->board = create_board(VISIBLE_VERTICAL_BOARD + INVISIBLE_BOARD, HORIZONTAL_BOARD);
    new_game->piece = create_piece();
    new_game->next_piece = create_piece();

    new_game->score = 0;
    new_game->level = 0;
    new_game->complete_lines = 0;

    return new_game;
}

void clean_game(Game* game) {
    	clean_board(game->board);
    	free(game->piece);
    	free(game->next_piece);
    	free(game);
}

void _ascend(Game* game) {
	for (int i = 0; i < 4; i++) {
 		game->piece->positions[i].y -= 1;
    	}
}

void check_state(Game* game) {
    if (has_colitions_bottom_or_remains(game->board, game->piece)) {
	_ascend(game);
        add_piece(game->board, game->piece);
        // Check Board for complete lines
        int complete_lines_quantity = delete_all_complete_lines(game->board);
        const unsigned int scores[4] = {40, 100, 300, 1200};

        game->score += scores[complete_lines_quantity - 1];
        game->complete_lines += complete_lines_quantity;

        // Get next piece
        copy(game->next_piece, game->piece);
	free(game->next_piece);
        game->next_piece = create_piece();
    }
}

void move_left(Game* game) {
	Piece piece_copy = *(game->piece);
    	for (int i = 0; i < 4; i++) {
        	piece_copy.positions[i].x -= 1;
	}
    	if (!has_colitions_border_or_remains(game->board, &piece_copy)) {
		copy(&piece_copy, game->piece);
	}
}

void move_right(Game* game) {
	Piece piece_copy = *(game->piece);
    	for (int i = 0; i < 4; i++) {
		piece_copy.positions[i].x += 1;
	}
    	if (!has_colitions_border_or_remains(game->board, &piece_copy)) {
		copy(&piece_copy, game->piece);
	}
}

void _move_left_no_colitions(Game* game) {
	Piece* piece = game->piece;
    	for (int i = 0; i < 4; i++) {
		piece->positions[i].x -= 1;
	}
}

void _move_right_no_colitions(Game* game) {
	Piece* piece = game->piece;
    	for (int i = 0; i < 4; i++) {
		piece->positions[i].x += 1;
	}
}

void descend(Game* game) {
	for (int i = 0; i < 4; i++) {
 		game->piece->positions[i].y += 1;
    	}
	check_state(game);
}

void rotate(Game* game) {
	Piece* piece = game->piece;
	Piece* old_piece = (Piece*) malloc(sizeof(Piece));
	copy(piece, old_piece);

	PointOnBoard center_point = get_center_point(piece);
	
	for (int i = 0; i < 4; i++) {
		unsigned int rotate_x = piece->positions[i].y - center_point.y;
		unsigned int rotate_y = piece->positions[i].x - center_point.x;         
		piece->positions[i].x = center_point.x - rotate_x;
		piece->positions[i].y =  center_point.y + rotate_y;
	}

	while (has_colitions_border_left(game->board, piece)) {
		_move_right_no_colitions(game);
	}

	while (has_colitions_border_right(game->board, piece)) {
		_move_left_no_colitions(game);
	}

	while (has_colitions_top(piece)) {
		descend(game);
	}

	if (has_colitions_remains(game->board, piece)) {
		free(piece);
		game->piece = old_piece;
	} else {
		free(old_piece);
	}
}

bool is_game_over(Game* game) {
    return get_row_quantity(game->board) > VERTICAL_SIZE;
}

void clean_for_cycle(Game* game) {
    if (game->complete_lines > 10 && game->level < 4) {
        game->complete_lines -= 10;
        game->level += 1;
    } 
}

unsigned int get_point_quantity(Game* game) {
    unsigned int point_quantity = 0;
    unsigned int row_len = get_row_quantity(game->board);
    for (unsigned int j = 0; j < row_len; j++)
    {
        unsigned int column_len = get_column_quantity(game->board, j);
        point_quantity += column_len;
    }

    return point_quantity + 4;
}

PointOnBoard* get_next_piece_points(Game* game) {

    PointOnBoard* points = (PointOnBoard*) malloc(sizeof(PointOnBoard) * 4);

    for (unsigned int i = 0; i < 4; i++)
    {
        PointOnBoard point = game->next_piece->positions[i];

        point.x += NEXT_PIECE_BLOCK_X + 2;
        point.y += NEXT_PIECE_BLOCK_Y;

        points[i] = point;
    }

    return points;
}

PointOnBoard* get_all_points(Game* game) {
    return game->board->occupied_board_points;
}
