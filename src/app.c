#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "button.c"
/* #include "game.c" *1/ */
#include "../classes/app.h"
#include "../classes/config.h"

/* SDL_Window* lost_message; */
/* Font font; */
/* Texture texturePoint; */
/* struct Game* game; */

/* const float delays_for_level[4] = {0.48, 0.43, 0.38, 0.33}; */




/* void draw_sprite(const unsigned int x, const unsigned int y, color point_color, Sprite& sprite) { */
/*     if (invisible_squares <= y) { */
/*         sprite.setTextureRect(IntRect(18*point_color, 0, 18, 18)); */
/*         sprite.setPosition(x*square_sixe, (y + header_squares)*square_sixe); */
/*     } */
/* } */

/* int main() */
/* { */
/*     if (!texturePoint.loadFromFile("images/tiles.png")) */
/*         throw("Texture load error"); */

/*     if (!font.loadFromFile("fonts/textFont.ttf")) */
/*         throw("Error al cargar la fuente"); */

/*     if (!music.openFromFile("sounds/theme.wav")) */
/*         throw("Error al cargar la música"); */

/*     SDL_Window* window = SDL_CreateWindow("Tetris!", */
/*                                        SDL_WINDOWPOS_CENTERED, */
/*                                        SDL_WINDOWPOS_CENTERED, */
/*                                        display_width + display_side_block_width, display_heigth, 0); */
/*     Game* game = createGame(); */

/*     Sprite sprite(texturePoint); */

/*     float scale = (float)square_sixe / 18; */
/*     sprite.setScale(scale, scale); */
    
/*     RectangleShape rectangle_header; */
/*     rectangle_header.setSize(Vector2f(display_width, display_header)); */
/*     rectangle_header.setFillColor(Color(190, 180, 180)); */

/*     RectangleShape rectangle_side_block; */
/*     rectangle_side_block.setSize(Vector2f(display_side_block_width, display_header + display_heigth)); */
/*     rectangle_side_block.setFillColor(Color(190, 180, 180)); */
/*     rectangle_side_block.setPosition(display_width, 0); */

/*     RectangleShape rectangle_next_piece; */
/*     rectangle_next_piece.setSize(Vector2f(display_next_piece_block_width, display_next_piece_block_heigth)); */
/*     rectangle_next_piece.setFillColor(Color::Black); */
/*     rectangle_next_piece.setPosition(display_next_piece_block_position_x, display_next_piece_block_position_y); */

/*     Text textScore; */

/*     textScore.setCharacterSize(24); */
/*     textScore.setStyle(Text::Bold); */
/*     textScore.setFont(font); */
/*     textScore.setFillColor(Color::Black); */

/*     float timer = 0, delay = 0; */
/*     Clock clock; */
    
/*     music.setLoop(true); */
/*     music.play(); */

/*     while (window->isOpen()) */
/*     { */
/*         delay = delays_for_level[game->level]; */
/*         float time = clock.getElapsedTime().asSeconds(); */
/*         clock.restart(); */
/*         timer += time; */

/*         Event event; */
/*         while (window->pollEvent(event)) { */
/*             if (event.type == Event::Closed) { */
/*                 window->close(); */
/*             } else if (event.type == Event::KeyPressed) { */
/*                 switch (event.key.code) */
/*                 { */
/*                     case Keyboard::Left: */
/*                         move_left(game); */
/*                         break; */
/*                     case Keyboard::Right: */
/*                         move_right(game); */
/*                         break; */
/*                     case Keyboard::Up: */
/*                         rotate(game); */
/*                         break; */
/*                     case Keyboard::Down: */
/*                         descend(game); */
/*                         break; */
/*                     default: */
/*                         break; */
/*                 } */
/*             } */
/*         } */
   

/*         window->clear(Color::Black); */

/*         window->draw(rectangle_header); */
/*         window->draw(rectangle_side_block); */
/*         window->draw(rectangle_next_piece); */
        
/*         // <--Tick--> */
/*         if (timer > delay) { */
/*             descend(game); */
/*             timer = 0; */
/*         } */

/*         check_state(game); */

/*         if (!is_game_over(game)) { */
/*             // Draw Points */
/*             Point* points = get_all_points(game); */
/*             unsigned int point_quantity = get_point_quantity(game); */

/*             for (unsigned int i = 0; i < point_quantity; i++) */
/*             { */
/*                 Point point = points[i]; */
/*                 draw_sprite(point.x, point.y, point.point_color, sprite); */
/*                 window->draw(sprite); */
/*             } */

/*             delete points; */
/*         } else { */
/*             render_game_over_window(); */
/*         } */

/*         clean_for_cycle(game); */

/*         textScore.setPosition(25, 30); */
/*         textScore.setString("Puntaje: " + to_string(game->score)); */
/*         window->draw(textScore); */

/*         textScore.setPosition(25, 60); */
/*         textScore.setString("Nivel: " + to_string(game->level)); */
/*         window->draw(textScore); */

/*         Point* points = get_next_piece_points(game); */
/*         for (unsigned int i = 0; i < 4; i++) */
/*         { */
/*             draw_sprite(points[i].x, points[i].y, points[i].point_color, sprite); */
/*             window->draw(sprite); */
/*         } */

/*         delete points; */

/*         window->display(); */
/*     } */
    
/*     delete window; */
/*     delete lost_message; */
/*     clean(game); */

/*     return 0; */
/* } */


App* app;

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app->window = SDL_CreateWindow("Tetris C", 
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       display_width + display_side_block_width, display_heigth, windowFlags);

	if (!app->window)
	{
		printf("Failed to open %d x %d window: %s\n", display_width + display_side_block_width, display_heigth, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

	if (!app->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void render_game_over_window() {
	app->lost_message = SDL_CreateWindow("Game Over!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_lost_message_width, display_lost_message_heigth, 0);
    
	app->font = TTF_OpenFont("Sans.ttf", 24);

	SDL_Color White = {255, 255, 255};

	app->surfaceMessage = TTF_RenderText_Solid(app->font, "Game Over!", Black);

	app->message = SDL_CreateTextureFromSurface(app->renderer, app->surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(app->renderer, app->message, NULL, &Message_rect);


    button_t accept_button = button_t { .draw_rect = SDL_RECT Vector2f(120, 80), Vector2f(120, 50) };

    function<void(void)> acceptClickEvent = [&]() {
        lost_message->close();
        clean(game);
        game = createGame();
    };

    accept_button.setClickEvent(acceptClickEvent);

    Button cancel_button("Cancelar", Vector2f(260, 80), Vector2f(120, 50), font);

    function<void(void)> cancelClickEvent = [&]() {
        lost_message->close();
        window->close();
    };

    cancel_button.setClickEvent(cancelClickEvent);

    while (lost_message->isOpen()) {
        Event event;
        while (lost_message->pollEvent(event)) {
            if (event.type == Event::Closed) {
                lost_message->close();
                window->close();
            }

            accept_button.update(event);
            cancel_button.update(event);
        }
        lost_message->clear(Color::Black);
        
        lost_message->draw(accept_button);
        lost_message->draw(cancel_button);
        lost_message->draw(text);
        lost_message->display();
    }        
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			default:
				break;
		}
	}
}

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
	SDL_RenderClear(app->renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app->renderer);
}

void cleanup() {
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	free(app);
}
