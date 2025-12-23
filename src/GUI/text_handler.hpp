#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Exception.hpp"

#include <string>
#include <utility>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

using std::string;

class TextHandler {
    sf::Font font;
    const string& str;
    sf::Text text;
    sf::RenderWindow& window;

public:
    explicit TextHandler(const string& str, const float object_x, const float object_y, const float object_width, const float object_height, sf::RenderWindow& window, const sf::Color color = sf::Color::Black, const int font_size = 30)
    : str{str}
    , text{font, str}
    , window{window}
    {
        if (!font.openFromFile("src/GUI/Jersey10-Regular.ttf")) {

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

    void render_text() const {
        window.draw(text);
    }
};
