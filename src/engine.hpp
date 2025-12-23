#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "config.hpp"
#include "state/menu_state.hpp"
#include "state/state.hpp"

inline constexpr double dt = 1.0 / 60.0;

class Engine {
    bool running = true;
    sf::Clock fpsClock;
    int frameCount = 0;
    float accumulator = 0.f;
    sf::RenderWindow window;

    State* current_state = nullptr;

public:
    Engine()
    : window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}),"Particle simulation | FPS: 0")
    {

    }

    void change_state(State* s) {
        assert(s != nullptr);
        if (current_state == s) return;
        delete current_state;
        current_state = s;
    }

    void run() {
        change_state(new MenuState(this, window));
        while (running) {
            handle_events();
            window.clear();
            current_state->handle_events();
            current_state->update(dt);
            current_state->render(window);
            window.display();
        }
        delete current_state;
        window.close();
    }

    void quit() {
        running = false;
    }

    void handle_events() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                quit();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    quit();
                }
            }
        }
    }
};
