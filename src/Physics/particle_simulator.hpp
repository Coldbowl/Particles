#pragma once

#include <vector>

#include "image_analyzer.hpp"
#include "Particle.hpp"

#include <SFML/Graphics/CircleShape.hpp>

using std::vector, std::sqrt;

class ParticleSimulator {
    vector<Particle> particles;

public:
    explicit ParticleSimulator(const int count) {
        if (count < 0) {
            throw std::invalid_argument("Bad argument!");
        }
        auto analyzer = ImageAnalyzer(count);
        analyzer.load_particle_positions();
        particles = analyzer.get_particles();
    }

    void update(const double dt) {
        for (Particle& p : particles) {
            p.update(dt);
        }
    }

    void render(sf::RenderWindow& window) const {
        for (const Particle& p : particles) {
            sf::CircleShape shape(p.radius);
            shape.setFillColor(p.color);
            shape.setPosition({p.position.x, p.position.y});
            window.draw(shape);
        }
    }
};