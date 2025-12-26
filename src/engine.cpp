#include <cassert>
#include <iostream>

#include "engine.hpp"
#include "state/menu_state.hpp"
#include "config.hpp"

Engine::Engine()
    : window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}),"Particle simulation")
{}

Engine::~Engine() {
    delete current_state;
}

void Engine::change_state(State* s) {
    assert(s != nullptr);
    if (current_state == s) return;
    delete current_state;
    current_state = s;
}

void Engine::run() {
    change_state(new MenuState(this, window));
    while (running) {
        accumulator += frame_clock.restart().asSeconds();
        handle_events();
        current_state->handle_events();

         while (accumulator >= dt) {
             current_state->update(dt);
             accumulator -= dt;
         }
        window.clear();
        current_state->render(window);
        window.display();
    }
    delete current_state;
    window.close();
}

void Engine::quit() {
    running = false;
}

void Engine::handle_events() {
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

// ParticleSimulator particle_simulator(1000);
//
// sf::RenderWindow window(
//     sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}),
//     "Particle simulation | FPS: 0");
//
// sf::Clock fpsClock;
// int frameCount = 0;
//
// while (window.isOpen()) {
//     accumulator += frameClock.restart().asSeconds();
//
//
//
//     window.clear();
//     particle_simulator.render(window);
//     window.display();
//
//     while (accumulator >= dt) {
//         particle_simulator.update(dt);
//         accumulator -= dt;
//     }
//

// }