#include "../classes/button.hpp"


Button::Button(const string text_string, const Vector2f location, const Vector2f size, Font font) {    
    RectangleShape rectagle;

    rectagle.setSize(size);
    rectagle.setPosition(location);

    this->rectagle = rectagle;

    this->text = text_string;

    this->font = font;
}

Button::~Button() {}

void Button::setText(const string text_string) {
    this->text = text_string;
}

void Button::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(this->rectagle, states);

    Text button_text;
    
    button_text.setCharacterSize(24);
    button_text.setStyle(Text::Bold);
    button_text.setFont(font);
    button_text.setFillColor(Color::Black);
    button_text.setString(this->text);
    button_text.setPosition(this->rectagle.getPosition());

    target.draw(button_text, states);
}

void Button::update(Event& event) 
{
    auto xCoord = event.mouseButton.x;
    auto yCoord = event.mouseButton.y;
    Vector2f worldPos = Vector2f(xCoord, yCoord);

    if (event.type == Event::MouseButtonPressed && this->rectagle.getGlobalBounds().contains(worldPos)) {
        this->clickEventFunction();
    }
}

void Button::setClickEvent(function<void(void)> eventFunction) {
    this->clickEventFunction = eventFunction;
}