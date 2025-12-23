#pragma once

#include <vector>

#include "../Physics/image_analyzer.hpp"
#include "../Physics/Particle.hpp"
#include "state.hpp"
#include "SFML/Graphics.hpp"

using std::vector;

class SimulationState : public State {
    vector<Particle> particles;

public:
    explicit SimulationState(const int count): State() {
        if (count < 0) {
            throw std::invalid_argument("Bad argument!");
        }
        auto analyzer = ImageAnalyzer(count);
        analyzer.load_particle_positions();
        particles = analyzer.get_particles();
    }

    void update(const double dt) override {
        for (Particle& p : particles) {
            p.update(dt);
        }
    }

    void render(sf::RenderWindow& window) override {
        for (const Particle& p : particles) {
            sf::CircleShape shape(p.radius);
            shape.setFillColor(p.color);
            shape.setPosition({p.position.x, p.position.y});
            window.draw(shape);
        }
    }

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