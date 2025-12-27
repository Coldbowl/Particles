#pragma once

#include "Vector.hpp"
#include "../config.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"

namespace sf { class Color; }

template<int Count>
class ImageAnalyzer {
    std::array<Vector, Count> particles;


public:
    ImageAnalyzer() = default;

    void load_particle_positions() {
        const int cols = static_cast<int>(std::ceil(std::sqrt(Count)));
        const int rows = static_cast<int>(std::ceil(static_cast<float>(Count) / cols));

        const float dx = static_cast<float>(SCREEN_WIDTH) / cols;
        const float dy = static_cast<float>(SCREEN_HEIGHT) / rows;
        for (int i = 0; i < Count; i++) {
            const int x = i % cols;
            const int y = i / cols;
            particles[i] = Vector{
                (x + 0.5f) * dx,
                (y + 0.5f) * dy
            };
        }
    }

    static std::array<sf::Color, Count> analyze_image() {
        std::array<sf::Color, Count> colors;

        sf::Image image;
        if (!image.loadFromFile("src/Image/particles_image.png")) {
            throw std::runtime_error("Failed to load image");
        }

        const auto size = image.getSize();
        const unsigned int w = size.x;
        const unsigned int h = size.y;

        const int cols = static_cast<int>(std::ceil(std::sqrt(Count)));
        const int rows = static_cast<int>(std::ceil(static_cast<float>(Count) / cols));

        const float dx = static_cast<float>(SCREEN_WIDTH)  / cols;
        const float dy = static_cast<float>(SCREEN_HEIGHT) / rows;

        for (int i = 0; i < Count; ++i) {
            const int gx = i % cols;
            const int gy = i / cols;

            const float sx = (gx + 0.5f) * dx;
            const float sy = (gy + 0.5f) * dy;

            unsigned int ix = std::min(
                static_cast<unsigned int>(sx * w / SCREEN_WIDTH),
                w - 1
            );
            unsigned int iy = std::min(
                static_cast<unsigned int>(sy * h / SCREEN_HEIGHT),
                h - 1
            );

            colors[i] = image.getPixel({ix, iy});
        }

        return colors;
    }

    [[nodiscard]] const std::array<Vector, Count>& get_particles() const {
        return particles;
    }
};
