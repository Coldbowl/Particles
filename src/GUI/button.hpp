#pragma once

#include <string>
#include <functional>

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
    sf::Color hover_color = sf::Color{128,128,128};

    TextHandler text_handler;

    sf::RectangleShape button;
    std::function<void()> on_click;



public:
    explicit Button(float button_x, float button_y, float button_width, float button_height, string text, sf::RenderWindow& window, std::function<void()> on_click, sf::Color color = sf::Color::White);

    void draw() const;

    bool is_hovering(const sf::Vector2i& mouse_position);

    void clicked() const;
};