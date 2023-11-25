#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;
using namespace std;

#ifndef BUTTON_HPP
#define BUTTON_HPP
class Button : public Drawable
{
private:
    RectangleShape rectagle;
    string text;
    function<void(void)> clickEventFunction;
    Font font;
public:
    Button(const string text_string, const Vector2f location, const Vector2f size, Font font);
    ~Button();
    void setText(const string text);
    void draw(RenderTarget& target, RenderStates states) const;
    void update(Event& event);
    void setClickEvent(function<void(void)> eventFunction);
};

#endif