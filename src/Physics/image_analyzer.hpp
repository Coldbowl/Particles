#pragma once
#include <vector>

#include "Particle.hpp"

class ImageAnalyzer {
    std::vector<Particle> particles;
    int count;

public:
    explicit ImageAnalyzer(int count);

    void load_particle_positions();

    [[nodiscard]] const std::vector<Particle>& get_particles() const;
};
