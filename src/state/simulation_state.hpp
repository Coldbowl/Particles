#pragma once

#include <vector>
#include "state.hpp"
#include "../config.hpp"
#include "../Physics/Vector.hpp"
#include "../Physics/Particles.hpp"

constexpr int denominator = 17; // NOTE: If you try to go under 17, the program crashes. Only the gods above know why.
constexpr int width  = SCREEN_WIDTH;
constexpr int height = SCREEN_HEIGHT;
constexpr int count  = (width * height) / denominator;

struct Particle; // Forward declaration

namespace sf { class RenderWindow; } // A clever foward declaration

class SimulationState final : public State {
    std::array<Vector, count> particles;
    Particles<count> particle_struct;

    sf::RenderWindow& window;

public:
    explicit SimulationState(Engine* engine, sf::RenderWindow& window);

    void update(float dt) override;

    void render(sf::RenderWindow& window) override;

    void enter() override;
    void exit() override;
    void handle_events() override;
};