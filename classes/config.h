// Square base sizes
#define square_size 20 

#define visible_vertical_board 20
#define horizontal_board 10
#define invisible_board 3
#define header 2
#define visible_board_x 1
#define visible_board_y 1

#define next_piece_block_horizontal 6
#define next_piece_block_vertical 7
#define next_piece_block_x (horizontal_board + visible_board_x + 1)
#define next_piece_block_y (header + invisible_board + 3)

#define horizontal_size (horizontal_board + next_piece_block_horizontal + visible_board_x + 2)
#define vertical_size (visible_vertical_board + invisible_board + 1)

#define score_horizontal 5
#define score_vertical 2
#define score_x next_piece_block_x
#define score_y (next_piece_block_y - 2)

// Display sizes
#define display_width square_size*horizontal_size
#define display_heigth square_size*vertical_size

#define display_board_width square_size*horizontal_board
#define display_board_heigth square_size*visible_vertical_board
#define display_board_x square_size*visible_board_x
#define display_board_y square_size*visible_board_y

#define display_lost_message_width 500
#define display_lost_message_heigth 200

#define display_next_piece_block_width square_size*next_piece_block_horizontal
#define display_next_piece_block_heigth square_size*next_piece_block_vertical 
#define display_next_piece_block_position_x square_size*next_piece_block_x
#define display_next_piece_block_position_y square_size*next_piece_block_y

#define display_score_wigth square_size*score_horizontal
#define display_score_heigth square_size*score_vertical
#define display_score_x square_size*score_x
#define display_score_y square_size*score_y

// Colors
#define black_color { .r = 0, .g = 0, .b = 0, .a = 255 }
#define white_color { .r = 255, .g = 255, .b = 255, .a = 255 }
