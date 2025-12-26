#include "image_analyzer.hpp"

#include <cstdint>

#include "SFML/Graphics/Color.hpp"
#include "../config.hpp"

ImageAnalyzer::ImageAnalyzer(const int denominator)
: denominator{denominator}
{
    width = SCREEN_WIDTH / denominator;
    height = SCREEN_HEIGHT / denominator;
    count = width * height;
    particles.reserve(count);
}

void ImageAnalyzer::load_particle_positions() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
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

const std::vector<Particle>& ImageAnalyzer::get_particles() const {
    return particles;
}