#pragma once

#include <cmath>
#include <iostream>

struct Vector {
    float x;
    float y;
    Vector() = default;
    Vector(const float x, const float y) : x(x), y(y) {}

    bool operator==(const Vector& v) const noexcept {
        return v.x == this->x && v.y == this->y;
    }

    bool operator!=(const Vector& v) const noexcept {
        return !(*this == v);
    }

    Vector operator+(const Vector& v) const noexcept {
        return {this->x + v.x, this->y + v.y };
    }

    Vector& operator+=(const Vector& v) noexcept {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector operator-(const Vector& v) const noexcept {
        return {this->x - v.x, this->y - v.y };
    }

    Vector& operator-=(const Vector& v) noexcept {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector operator*(const float f) const noexcept {
        return {this->x * f, this->y * f};
    }

    Vector& operator*=(const float f) noexcept {
        this->x *= f;
        this->y *= f;
        return *this;
    }

    Vector operator/(const float f) const noexcept {
        return {this->x / f, this->y * f};
    }

    [[nodiscard]] float length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    [[nodiscard]] Vector normalized() const noexcept {
        const float l = length();
        return {this->x / l, this->y / l};
    }
};
inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}


inline Vector operator*(const float f, const Vector& v) noexcept {
    return {v.x * f, v.y * f};
}

inline float dot(const Vector a, const Vector b) {
    return a.x * b.x + a.y * b.y;
}