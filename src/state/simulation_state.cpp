#include "simulation_state.hpp"
#include "state.hpp"
#include "../Physics/image_analyzer.hpp"

#include <SFML/Graphics.hpp>
#include <array>

int frameCount = 0;
sf::Clock fpsClock;

SimulationState::SimulationState(Engine* engine)
    : State(engine)
    , particles([]{
        ImageAnalyzer<count> analyzer;
        analyzer.load_particle_positions();
        return analyzer.get_particles();
    }()) // direct initialization
    , particle_struct{particles}
{
    ImageAnalyzer<count> analyzer;
    analyzer.load_particle_positions();
    particles = std::move(analyzer.get_particles());

    std::cout << "Simulating with " << count << " particles\n";
}

void SimulationState::update(const float dt)  {
    particle_struct.update(dt);
}

void SimulationState::render(sf::RenderWindow& window)  {
    particle_struct.render(window);
    frameCount++;
    if (fpsClock.getElapsedTime().asSeconds() >= 1.f) {
        window.setTitle("Particle simulation | FPS: " + std::to_string(frameCount));
        frameCount = 0;
        fpsClock.restart();
    }
}

void SimulationState::enter() {

}

void SimulationState::exit() {

}

void SimulationState::handle_events() {

}
