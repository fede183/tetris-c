#include "classes/config.h"
#include "classes/piece.h"
#include "classes/game.h"
#include "board.c"
#include <math.h>

Game* init_game() {
    Game* new_game = (Game*) malloc(sizeof(Game));
    // Declare Game
    new_game->board = create_board(VISIBLE_VERTICAL_BOARD + INVISIBLE_BOARD, HORIZONTAL_BOARD);
    new_game->piece = create_piece();
    new_game->next_piece = create_piece();

    new_game->score = 0;
    new_game->level = 1;
    new_game->complete_lines = 0;
    new_game->current_cycle = 0;

    return new_game;
}

bool is_game_over(Game* game) {
    return has_colitions_top_and_remains(game->board, game->piece);
}

void clean_game(Game* game) {
    	clean_board(game->board);
    	free(game->piece);
    	free(game->next_piece);
    	free(game);
}

void _move(Piece* piece, int x, int y) {
	for (unsigned int i = 0; i < 4; i++) {
 		piece->positions[i].x += x;
 		piece->positions[i].y += y;
    	}
	piece->center_point.x += x;
	piece->center_point.y += y;
}

void _verify_piece_after_move(Game* game, Piece* piece) {
    	if (!has_colitions_border_or_remains(game->board, piece)) {
		free(game->piece);
		game->piece = piece;
	}
}

void _ascend(Game* game) {
	_move(game->piece, 0, -1);
}

void check_state(Game* game) {
    if (has_colitions_bottom_or_remains(game->board, game->piece)) {
	_ascend(game);
        add_piece(game->board, game->piece);
        // Check Board for complete lines
        const unsigned int complete_lines_quantity = delete_all_complete_lines(game->board);

        game->score += SCORES_PER_COMPLETE_LINES[complete_lines_quantity];
        game->complete_lines += complete_lines_quantity;

        // Get next piece
        copy(game->next_piece, game->piece);
	free(game->next_piece);
        game->next_piece = create_piece();
    }
}

void move_left(Game* game) {
	Piece* piece_copy = (Piece*) malloc(sizeof(Piece));
	copy(game->piece, piece_copy);
	_move(piece_copy, -1, 0);
	_verify_piece_after_move(game, piece_copy);
}

void move_right(Game* game) {
	Piece* piece_copy = (Piece*) malloc(sizeof(Piece));
	copy(game->piece, piece_copy);
	_move(piece_copy, 1, 0);
	_verify_piece_after_move(game, piece_copy);
}

void _move_left_no_colitions(Game* game) {
	Piece* piece = game->piece;
	_move(piece, -1, 0);
}

void _move_right_no_colitions(Game* game) {
	Piece* piece = game->piece;
	_move(piece, 1, 0);
}

void descend(Game* game) {
	_move(game->piece, 0, 1);
	check_state(game);
}

void rotate(Game* game) {
	Piece* piece = game->piece;
	Piece* old_piece = (Piece*) malloc(sizeof(Piece));
	copy(piece, old_piece);

	CenterPoint center_point = piece->center_point;
	float beta = M_PI / 2.0;
	float beta_cos = cos(beta);
	float beta_sin = sin(beta);
	
	for (unsigned int i = 0; i < 4; i++) {
		float rotate_x = ((float) piece->positions[i].x) - center_point.x;
		float rotate_y = - (((float) piece->positions[i].y) - center_point.y);

		float prima_x = (rotate_x * beta_cos) - (rotate_y * beta_sin);
		float prima_y = (rotate_x * beta_sin) + (rotate_y * beta_cos);

		piece->positions[i].x = round(center_point.x + prima_x);
		piece->positions[i].y = round(center_point.y - prima_y);
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

PointOnBoard* get_all_points(Game* game) {
    return game->board->occupied_board_points;
}
