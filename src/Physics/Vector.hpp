#pragma once

#include <cmath>

struct Vector {
    double x;
    double y;
    Vector(const double x,const double y) : x(x), y(y) {}

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

    Vector operator*(const double f) const noexcept {
        return {this->x * f, this->y * f};
    }

    Vector& operator*=(const double f) noexcept {
        this->x *= f;
        this->y *= f;
        return *this;
    }

    Vector operator/(const double d) const noexcept {
        return {this->x / d, this->y * d};
    }

    [[nodiscard]] double length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    [[nodiscard]] Vector normalized() const noexcept {
        double l = length();
        return {this->x / l, this->y / l};
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

inline Vector operator*(const double d, const Vector& v) noexcept {
    return {v.x * d, v.y * d};
}