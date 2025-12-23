#pragma once
#include <cstdint>
#include <vector>

#include "Particle.hpp"
#include "SFML/Graphics/Color.hpp"

class ImageAnalyzer {
    std::vector<Particle> particles;
    int count;

public:
    explicit ImageAnalyzer(const int count) : count{count} {
        particles.reserve(count);
    }

    void load_particle_positions() {
        const int n = static_cast<int>(std::sqrt(count));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                const Vector pos {50 + i * 10.f, 50 + j * 10.f};

                const auto r = static_cast<uint8_t>(255);
                const auto g = static_cast<uint8_t>(i/sqrt(count) * 255);
                const auto b = static_cast<uint8_t>(j/sqrt(count) * 255);

                particles.emplace_back(
                    pos,
                    sf::Color{r,g,b}
                );
            }
        }
    }

    [[nodiscard]] const std::vector<Particle>& get_particles() const {
        return particles;
    }
};
