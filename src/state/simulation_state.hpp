#pragma once

#include <vector>
#include "state.hpp"
#include "../config.hpp"
#include "../Physics/Vector.hpp"
#include "../Physics/Particles.hpp"

constexpr int denominator = 5;
constexpr int width  = SCREEN_WIDTH / denominator;
constexpr int height = SCREEN_HEIGHT / denominator;
constexpr int count  = width * height;

struct Particle; // Forward declaration

namespace sf { class RenderWindow; } // A clever foward declaration

class SimulationState final : public State {
    std::array<Vector, count> particles;
    Particles<count> particle_struct;


public:
    explicit SimulationState(Engine* engine);

    void update(float dt) override;

    void render(sf::RenderWindow& window) override;

    void enter() override;
    void exit() override;
    void handle_events() override;
};