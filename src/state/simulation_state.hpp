#pragma once

#include <vector>
#include "state.hpp"

struct Particle; // Forward declaration

namespace sf { class RenderWindow; } // A clever foward declaration

class SimulationState  : public State {
    std::vector <Particle> particles;

public:
    explicit SimulationState(Engine* engine, int count);

    void update(const double dt) override;

    void render(sf::RenderWindow& window) override;

    void enter() override = 0;
    void exit() override = 0;
    void handle_events() override = 0;
};


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
//     frameCount++;
//     if (fpsClock.getElapsedTime().asSeconds() >= 1.f) {
//         window.setTitle("Particle simulation | FPS: " + std::to_string(frameCount));
//         frameCount = 0;
//         fpsClock.restart();
//     }
// }