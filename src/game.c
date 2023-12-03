#include "../classes/config.h"
#include "../classes/piece.h"
#include "../classes/game.h"
#include "board.c"

Game* createGame() {
    Game* newGame = (Game*) malloc(sizeof(Game));
    // Declare Game
    newGame->board = create_board(complete_vertical_squares, horizontal_squares);
    newGame->piece = createPiece();
    newGame->backout_piece = createPiece();
    copy(newGame->piece, newGame->backout_piece);
    newGame->next_piece = createPiece();

    newGame->score = 0;
    newGame->level = 0;
    newGame->complete_lines = 0;

    return newGame;
}

void clean_game(Game* game) {
    clean_board(game->board);
    free(game->piece);
    free(game);
}

void move_left(Game* game) {
    for (int i = 0; i < 4; i++) {
        game->piece->positions[i].x -= 1;
    }
    if (has_colitions_border_or_remains(game->board, game->piece)) 
        copy(game->backout_piece, game->piece);
}

void move_right(Game* game) {
    for (int i = 0; i < 4; i++) {
        game->piece->positions[i].x += 1;
    }
    if (has_colitions_border_or_remains(game->board, game->piece)) 
        copy(game->backout_piece, game->piece);
}

void descend(Game* game) {
    for (int i = 0; i < 4; i++) {
        game->piece->positions[i].y += 1;
    }
}

void rotate(Game* game) {
    Point center_point = game->piece->positions[1];
    for (int i = 0; i < 4; i++) {
        unsigned int rotate_x = game->piece->positions[i].y - center_point.y;
        unsigned int rotate_y = game->piece->positions[i].x - center_point.x;         
        game->piece->positions[i].x = center_point.x - rotate_x;
        game->piece->positions[i].y =  center_point.y + rotate_y;

    }

    while (has_colitions_border_or_remains(game->board, game->piece)) {
        move_right(game);
    }

    while (has_colitions_top(game->piece)) {
        descend(game);
    }

}

bool is_game_over(Game* game) {
    return get_row_quantity(game->board) > vertical_squares;
}

void clean_for_cycle(Game* game) {
    if (game->complete_lines > 10 && game->level < 4) {
        game->complete_lines -= 10;
        game->level += 1;
    } 
    copy(game->piece, game->backout_piece);
}

void check_state(Game* game) {
    if (has_colitions_bottom_or_remains(game->board, game->piece)) {
        copy(game->backout_piece, game->piece);
        add_piece(game->board, game->piece);
        // Check Board for complete lines
        int complete_lines_quantity = delete_all_complete_lines(game->board);
        const unsigned int scores[4] = {40, 100, 300, 1200};

        game->score += scores[complete_lines_quantity - 1];
        game->complete_lines += complete_lines_quantity;

        // Get next piece
        copy(game->next_piece, game->piece);
        game->next_piece = createPiece();
        copy(game->piece, game->backout_piece);
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

    PointOnBoard* point = (Point*) malloc(sizeof(Point) * 4);

    for (unsigned int i = 0; i < 4; i++)
    {
        Point point = game->next_piece->positions[i];

        point.x += next_piece_block_position_x + 2;
        point.y += next_piece_block_position_y;

        points[i] = point;
    }

    return points;
}

PointOnBoard* get_all_points(Game* game) {

    PointOnBoard* points = game->board->occupied_board_points;

    return points;
}
