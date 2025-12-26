#include "text_handler.hpp"

using std::string;

TextHandler::TextHandler(const string& str, const float object_x, const float object_y, const float object_width, const float object_height, sf::RenderWindow& window, const sf::Color color, const int font_size)
: str{std::move(str)}
, text{font, str}
, window{window}
{
    if (!font.openFromFile("src/GUI/Jersey10-Regular.ttf")) {
        // the function called in the if-statement crashes the program I think, so no need to error-handle
    }
    text.setCharacterSize(font_size);

    const sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    text.setPosition({
        object_x + object_width  / 2.f,
        object_y + object_height / 2.f
    });

    text.setFillColor(color);
}

void TextHandler::render_text() const {
    window.draw(text);
}
