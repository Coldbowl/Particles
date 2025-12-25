#pragma once

#include <string>

#include "text_handler.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Color.hpp"


using std::string;

namespace sf { class RenderWindow; }

class Button {
    float button_x;
    float button_y;
    float button_width;
    float button_height;
    string text;
    sf::RenderWindow& window;
    sf::Color color;

    TextHandler text_handler;

    sf::RectangleShape button;
    void (*on_click)();

public:
    explicit Button(const float button_x, const float button_y, const float button_width, const float button_height, string text, sf::RenderWindow& window, void(*on_click)(), const sf::Color color);

    void draw() const;

    bool is_hovering(const sf::Vector2i& mouse_position) const;

    void clicked() const;
};