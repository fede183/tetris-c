#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <functional>

#include "src/button.cpp"
#include "src/game.cpp"

using namespace std;
using namespace sf;

RenderWindow* window;
RenderWindow* lost_message;
Font font;
Texture texturePoint;
Music music;
Game* game;

const float delays_for_level[4] = {0.48, 0.43, 0.38, 0.33};

void render_game_over_window() {
    lost_message = new RenderWindow(VideoMode(display_lost_message_width, display_lost_message_heigth), "Game Over!");
    
    Text text;

    text.setCharacterSize(24);
    text.setStyle(Text::Bold);
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setPosition(25, 30);
    text.setString("Game Over!");

    Button accept_button("Aceptar", Vector2f(120, 80), Vector2f(120, 50), font);

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


void draw_sprite(const unsigned int x, const unsigned int y, color point_color, Sprite& sprite) {
    if (invisible_squares <= y) {
        sprite.setTextureRect(IntRect(18*point_color, 0, 18, 18));
        sprite.setPosition(x*square_sixe, (y + header_squares)*square_sixe);
    }
}

int main()
{
    if (!texturePoint.loadFromFile("images/tiles.png"))
        throw("Texture load error");

    if (!font.loadFromFile("fonts/textFont.ttf"))
        throw("Error al cargar la fuente");

    if (!music.openFromFile("sounds/theme.wav"))
        throw("Error al cargar la música");

    RenderWindow* window = new RenderWindow(VideoMode(display_width + display_side_block_width, display_heigth), "Tetris!");
    Game* game = createGame();

    Sprite sprite(texturePoint);

    float scale = (float)square_sixe / 18;
    sprite.setScale(scale, scale);
    
    RectangleShape rectangle_header;
    rectangle_header.setSize(Vector2f(display_width, display_header));
    rectangle_header.setFillColor(Color(190, 180, 180));

    RectangleShape rectangle_side_block;
    rectangle_side_block.setSize(Vector2f(display_side_block_width, display_header + display_heigth));
    rectangle_side_block.setFillColor(Color(190, 180, 180));
    rectangle_side_block.setPosition(display_width, 0);

    RectangleShape rectangle_next_piece;
    rectangle_next_piece.setSize(Vector2f(display_next_piece_block_width, display_next_piece_block_heigth));
    rectangle_next_piece.setFillColor(Color::Black);
    rectangle_next_piece.setPosition(display_next_piece_block_position_x, display_next_piece_block_position_y);

    Text textScore;

    textScore.setCharacterSize(24);
    textScore.setStyle(Text::Bold);
    textScore.setFont(font);
    textScore.setFillColor(Color::Black);

    float timer = 0, delay = 0;
    Clock clock;
    
    music.setLoop(true);
    music.play();

    while (window->isOpen())
    {
        delay = delays_for_level[game->level];
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code)
                {
                    case Keyboard::Left:
                        move_left(game);
                        break;
                    case Keyboard::Right:
                        move_right(game);
                        break;
                    case Keyboard::Up:
                        rotate(game);
                        break;
                    case Keyboard::Down:
                        descend(game);
                        break;
                    default:
                        break;
                }
            }
        }
   

        window->clear(Color::Black);

        window->draw(rectangle_header);
        window->draw(rectangle_side_block);
        window->draw(rectangle_next_piece);
        
        // <--Tick-->
        if (timer > delay) {
            descend(game);
            timer = 0;
        }

        check_state(game);

        if (!is_game_over(game)) {
            // Draw Points
            Point* points = get_all_points(game);
            unsigned int point_quantity = get_point_quantity(game);

            for (unsigned int i = 0; i < point_quantity; i++)
            {
                Point point = points[i];
                draw_sprite(point.x, point.y, point.point_color, sprite);
                window->draw(sprite);
            }

            delete points;
        } else {
            render_game_over_window();
        }

        clean_for_cycle(game);

        textScore.setPosition(25, 30);
        textScore.setString("Puntaje: " + to_string(game->score));
        window->draw(textScore);

        textScore.setPosition(25, 60);
        textScore.setString("Nivel: " + to_string(game->level));
        window->draw(textScore);

        Point* points = get_next_piece_points(game);
        for (unsigned int i = 0; i < 4; i++)
        {
            draw_sprite(points[i].x, points[i].y, points[i].point_color, sprite);
            window->draw(sprite);
        }

        delete points;

        window->display();
    }
    
    delete window;
    delete lost_message;
    clean(game);

    return 0;
}