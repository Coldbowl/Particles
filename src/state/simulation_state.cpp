#include "simulation_state.hpp"

#include "state.hpp"
#include "../Physics/image_analyzer.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <SFML/Window/Keyboard.hpp>

#include "menu_state.hpp"
#include "../engine.hpp"

int frameCount = 0;
sf::Clock fpsClock;

SimulationState::SimulationState(Engine* engine, sf::RenderWindow& window)
    : State(engine)
    , particles([]{
        ImageAnalyzer<count> analyzer{};
        analyzer.load_particle_positions();
        return analyzer.get_particles();
    }()) // direct initialization
    , particle_struct{particles}
    , window{window}
{
    ImageAnalyzer<count> analyzer{};
    analyzer.load_particle_positions();
    particles = analyzer.get_particles();
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        engine->change_state(new MenuState(this->engine, window));
    }
}

