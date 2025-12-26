#pragma once

#include <vector>
#include "state.hpp"

struct Particle; // Forward declaration

namespace sf { class RenderWindow; } // A clever foward declaration

class SimulationState final : public State {
    std::vector <Particle> particles;

public:
    explicit SimulationState(Engine* engine, int count = 1000);

    void update(double dt) override;

    void render(sf::RenderWindow& window) override;

    void enter() override;
    void exit() override;
    void handle_events() override;
};