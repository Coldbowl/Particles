#include "simulation_state.hpp"
#include "state.hpp"
#include "../Physics/image_analyzer.hpp"
#include "../Physics/Particle.hpp"

#include <SFML/Graphics.hpp>


SimulationState::SimulationState(Engine* engine, const int count)
    : State(engine)
{
    if (count < 0) {
        throw std::invalid_argument("Bad argument!");
    }
    auto analyzer = ImageAnalyzer(count);
    analyzer.load_particle_positions();
    particles = analyzer.get_particles();
}

void SimulationState::update(const double dt)  {
    for (Particle& p : particles) {
        p.update(dt);
    }
}

void SimulationState::render(sf::RenderWindow& window)  {
    for (const Particle& p : particles) {
        sf::CircleShape shape(p.radius);
        shape.setFillColor(p.color);
        shape.setPosition({p.position.x, p.position.y});
        window.draw(shape);
    }
}