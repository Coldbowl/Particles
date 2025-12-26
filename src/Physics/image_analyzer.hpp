#pragma once

#include "Vector.hpp"
#include "../config.hpp"

template<int Count>
class ImageAnalyzer {
    std::array<Vector, Count> particles;
    int denominator;

public:
    ImageAnalyzer() = default;

    void load_particle_positions() {
        for (int i = 0; i < Count; i++) {
            // particles[i] = { 10 * i % SCREEN_WIDTH, SCREEN_HEIGHT * i / 1000};
            particles[i] = Vector{
                static_cast<float>(i % (SCREEN_WIDTH / 10)) * 10.f,
                static_cast<float>(i / (SCREEN_WIDTH / 10)) * 10.f
            };
        }
    }

    [[nodiscard]] const std::array<Vector, Count>& get_particles() const{
        return particles;
    }
};
