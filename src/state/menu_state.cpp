#include "menu_state.hpp"
#include "../config.hpp"

#include <array>
#include <memory>
#include <iostream>

#include "state.hpp"
#include "../GUI/button.hpp"

MenuState::MenuState(Engine* engine, sf::RenderWindow& window)
    : State(engine)
    , window{window}
    , title_text{
        "Particle Simulator",
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        window,
        sf::Color::Cyan,
        100
    }
{
    buttons[0] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 3.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        "Simulate",
        window,
        []() {
            std::cout << "You clicked Simulate!\n";
            // engine->change_state(new SimulationState(engine));
        }
    );
    buttons[1] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 4.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
    "Upload Image",
        window, []() {
            std::cout << "You clicked Upload Image\n";
        }
    );
    buttons[2] = std::make_unique<Button>(
        SCREEN_WIDTH / 10.0,
        SCREEN_HEIGHT * 5.0 / 6.0,
        SCREEN_WIDTH * 4.0 / 5.0,
        SCREEN_HEIGHT / 10.0,
        "Preferences",
        window,
        []() {
            std::cout << "You clicked Preferences\n";
        }
    );
}

void MenuState::update(double dt) {
    position = sf::Mouse::getPosition(window);
}

void MenuState::render(sf::RenderWindow& window) {
    title_text.render_text();

    is_hovering = false;
    for (const auto& btn : buttons) {
        if (!btn) continue;

        Button& b = *btn;

        if (b.is_hovering(position)) {
            hovered_button = &b;
            is_hovering = true;
        }
        b.draw(); // <---- The reason all of this is even in render, is because of this cheeky call
    }
    if (!is_hovering) {
        hovered_button = nullptr;
    }
}

void MenuState::enter()  {
    // TODO: code for when this state becomes active
}

void MenuState::exit()  {
    // TODO: code for when this state exits
}

void MenuState::handle_events()  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (!pressed) {
            if (hovered_button != nullptr) hovered_button->clicked();
            else std::cout << "You ain't clicking nothing, cuh\n";
            pressed = true;
        }
    } else {
        pressed = false;
    }
}
