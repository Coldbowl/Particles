#pragma once

#include <array>
#include <random>
#include <algorithm>
#include <execution>
#include <ranges>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../config.hpp"
#include "Vector.hpp"

using std::clamp;

inline std::mt19937 rng(std::random_device{}());

inline std::uniform_real_distribution<float> pos_dist_x(0.f, SCREEN_WIDTH);
inline std::uniform_real_distribution<float> pos_dist_y(0.f, SCREEN_HEIGHT);
inline std::uniform_real_distribution velDist(-2.f, 2.f);

inline constexpr float power = 10.f;
inline constexpr float k = 5.f; // attraction strength
inline constexpr float c = 2.f; // damping (friction)

template<int Count>
struct Particles {
    sf::VertexArray vertices;

    std::array<Vector, Count> position;
    std::array<Vector, Count> velocity;
    std::array<Vector, Count> target_position;
    std::array<sf::Color, Count> color;
    const float radius = 2.f;

    explicit Particles(std::array<Vector, Count> target_position)
    : vertices(sf::PrimitiveType::Points, Count),
      target_position(std::move(target_position))
    {
        for (int i = 0; i < Count; i++) {
            position[i] = { pos_dist_x(rng), pos_dist_y(rng) };
            velocity[i] = { velDist(rng), velDist(rng) };
            color[i] = sf::Color{
                static_cast<uint8_t>(127 + 127 * std::sin(0.05f * i)),
                static_cast<uint8_t>(127 + 127 * std::sin(0.05f * i + 2.1f)),
                static_cast<uint8_t>(127 + 127 * std::sin(0.05f * i + 4.2f))
            };
        }
    }

    void update(const float dt) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < Count; i++) {
            Vector acc = (target_position[i] - position[i]) * k - velocity[i] * c;
            velocity[i] += acc * dt;
            position[i] += velocity[i] * dt * power;

            // branchless reflection
            float max_x = SCREEN_WIDTH - radius;
            float max_y = SCREEN_HEIGHT - radius;

            position[i].x = max_x - std::abs(max_x - position[i].x);
            position[i].y = max_y - std::abs(max_y - position[i].y);

            velocity[i].x *= ((position[i].x - max_x) * (position[i].x - max_x) > 0.f) ? -1.f : 1.f;
            velocity[i].y *= ((position[i].y - max_y) * (position[i].y - max_y) > 0.f) ? -1.f : 1.f;

            // branchless snap to target
            const Vector d = target_position[i] - position[i];
            const float dist2 = dot(d,d);
            const float snap = std::min(dist2 / 0.5f, 1.f);

            position[i] = target_position[i] + (position[i] - target_position[i]) * snap;
            velocity[i] *= snap;
        }
    }

    void render(sf::RenderWindow& window) {
        for (size_t i = 0; i < Count; i++) {
            vertices[i].position = {
                position[i].x,
                position[i].y
            };
            vertices[i].color = color[i];
        }
        window.draw(vertices);
    }
};