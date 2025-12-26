#pragma once

#include "state.hpp"
#include "../GUI/button.hpp"

class Engine;
namespace sf { class RenderWindow; }

class MenuState final : public State {
    sf::RenderWindow& window;

    std::array<std::unique_ptr<Button>, 3> buttons;

    TextHandler title_text;

    Button* hovered_button = nullptr;
    sf::Vector2i position;

    bool is_hovering = false;
    bool pressed = false;
public:
    explicit MenuState(Engine* engine, sf::RenderWindow& window);

    void update(float dt) override;

    void render(sf::RenderWindow& window) override;

    void enter() override;

    void exit() override;

    void handle_events() override;
};
