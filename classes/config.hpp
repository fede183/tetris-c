
    #define square_sixe 20 
    #define horizontal_squares 10
    #define vertical_squares 27
    #define invisible_squares 3
    #define header_squares 2
    #define side_block_width 8
    #define complete_vertical_squares (vertical_squares + invisible_squares)
    #define display_width (square_sixe*horizontal_squares)
    #define display_side_block_width (square_sixe*side_block_width)
    #define display_heigth (square_sixe*(vertical_squares + header_squares + invisible_squares))
    #define display_header (square_sixe*(header_squares + invisible_squares))
    
    #define display_lost_message_width 500
    #define display_lost_message_heigth 200
    
    #define next_piece_block_width 6
    #define next_piece_block_heigth 7
    #define display_next_piece_block_width (square_sixe*next_piece_block_width)
    #define display_next_piece_block_heigth (square_sixe*next_piece_block_heigth) 
    #define next_piece_block_position_x (horizontal_squares + 1)
    #define next_piece_block_position_y (header_squares + invisible_squares + 3)
    #define display_next_piece_block_position_x square_sixe*next_piece_block_position_x
    #define display_next_piece_block_position_y square_sixe*next_piece_block_position_y

