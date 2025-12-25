#pragma once

#include <random>
#include <iostream>
#include <algorithm>

#include "Vector.hpp"
#include "../config.hpp"

using std::cout, std::clamp;

inline constexpr double power_coefficient = 10.0;

inline std::mt19937 rng(std::random_device{}());

inline std::uniform_real_distribution<double> pos_dist_x(0.f, SCREEN_WIDTH);
inline std::uniform_real_distribution<double> pos_dist_y(0.f, SCREEN_HEIGHT);
inline std::uniform_real_distribution<double> velDist(-2.f, 2.f);

inline const double k = 5.0; // attraction strength
inline const double c = 2.0; // damping (friction)

struct Particle {
    Vector position;
    Vector target_position;
    Vector velocity;
    sf::Color color;
    double radius;

    explicit Particle(const Vector target_position, const sf::Color color, const double radius = 2.0)
    : position {pos_dist_x(rng), pos_dist_y(rng) }
    , target_position{ target_position }
    , velocity { velDist(rng), velDist(rng) }
    , color{ color }
    , radius{ radius } {
    }

    void update(const double dt) {
        const Vector acceleration = (target_position - position) * k - velocity * c;
        velocity += acceleration * dt;
        position += velocity * dt * power_coefficient;

        const double diameter = 2 * radius;

        // Checking for collision
        if (position.x < 0) {
            position.x = 0.0;
            velocity.x *= -1;
        }
        else if (position.x > SCREEN_WIDTH - diameter) {
            position.x = 2.0 * (SCREEN_WIDTH - diameter) - position.x;
            velocity.x *= -1;
        }

        if (position.y < 0) {
            position.y = 0.0;
            velocity.y *= -1;
        }
        else if (position.y > SCREEN_HEIGHT - diameter) {
            position.y = 2.0 * (SCREEN_HEIGHT - diameter) - position.y;
            velocity.y *= -1;
        }

        if (target_position.length() < 0.5) {
            velocity = {0.0, 0.0};
            position = target_position;
        }
    }


    void print() const {
        cout << "Target position: " << target_position << ". Position: " << position << ". Velocity: " << velocity << "\n";
    }
};