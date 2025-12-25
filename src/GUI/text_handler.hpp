#pragma once
#include "SFML/Graphics/Font.hpp"

#include <string>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

using std::string;

namespace sf { class RenderWindow; }

class TextHandler {
    sf::Font font;
    const string& str;
    sf::Text text;
    sf::RenderWindow& window;

public:
    explicit TextHandler(string& str, float object_x, float object_y, float object_width, float object_height, sf::RenderWindow& window, sf::Color color, int font_size);

    void render_text() const;
};
