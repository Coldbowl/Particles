#include "button.hpp"

#include <string>

#include "text_handler.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using std::string;

Button::Button(const float button_x, const float button_y, const float button_width, const float button_height, const string text, sf::RenderWindow& window, void(*on_click)(), const sf::Color color = sf::Color::White)
: button_x{button_x}
, button_y{button_y}
, button_width{button_width}
, button_height{button_height}
, text{std::move(text)}
, window{window}
, color{color}
, text_handler(this->text, button_x, button_y, button_width, button_height, window)
, on_click{on_click}
{
    button.setPosition({button_x, button_y});
    button.setSize({button_width, button_height});
    button.setFillColor(color);
}

void Button::draw() const {
    window.draw(button);
    text_handler.render_text();
}

bool Button::is_hovering(const sf::Vector2i& mouse_position) const {
    // 662, 375
    return mouse_position.x > button_x && mouse_position.x < button_x + button_width && mouse_position.y > button_y  && mouse_position.y < button_y + button_height;
}

void Button::clicked() const {
    if (on_click) {
        on_click();
    }
}
