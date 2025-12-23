#pragma once

#include "simulation_state.hpp"
#include "state.hpp"
#include "../GUI/button.hpp"
#include "../config.hpp"
#include "../engine.hpp"

class MenuState final : public State {
    sf::RenderWindow& window;
    Button buttons[3] = {
        {
            SCREEN_WIDTH / 10.0,
            SCREEN_HEIGHT * 3.0 / 6.0,
            SCREEN_WIDTH * 4.0 / 5.0, SCREEN_HEIGHT / 10.0,
            "Simulate",
            window,
            []() {
                std::cout << "You clicked simulate\n";
            }
        },
        {
            SCREEN_WIDTH / 10.0,
            SCREEN_HEIGHT * 4.0 / 6.0,
            SCREEN_WIDTH * 4.0 / 5.0,
            SCREEN_HEIGHT / 10.0,
        "Upload Image",
            window, []() {
                std::cout << "You clicked Upload Image\n";
            }
        },
        {
            SCREEN_WIDTH / 10.0,
            SCREEN_HEIGHT * 5.0 / 6.0,
            SCREEN_WIDTH * 4.0 / 5.0,
            SCREEN_HEIGHT / 10.0,
            "Preferences",
            window,
            []() {
                std::cout << "You clicked Preferences\n";
            }
        },
    };

    TextHandler title_text;

    Button* hovered_button = nullptr;
    sf::Vector2i position;

    bool is_hovering = false;
    bool pressed = false;

public:
    explicit MenuState(Engine* engine, sf::RenderWindow& window)
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
        100}
    {}

    void update(double dt) override {
        position = sf::Mouse::getPosition(window);
    }

    void render(sf::RenderWindow& window) override {
        title_text.render_text();

        is_hovering = false;
        for (Button& b : buttons) {
            if (buttons->is_hovering(position)) {
                hovered_button = &b;
                is_hovering = true;
            }
            b.draw(); // <---- The reason all of this is even in render, is because of this cheeky call
        }
        if (!is_hovering) {
            hovered_button = nullptr;
        }
    }

    void enter() override {
        // TODO: code for when this state becomes active
    }

    void exit() override {
        // TODO: code for when this state exits
    }

    void handle_events() override {
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
};
