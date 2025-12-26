#pragma once
#include <vector>

#include "Particle.hpp"

class ImageAnalyzer {
    std::vector<Particle> particles;
    int count;
    int denominator;
    float width;
    float height;

public:
    explicit ImageAnalyzer(int denominator);

    void load_particle_positions();

    [[nodiscard]] const std::vector<Particle>& get_particles() const;
};
