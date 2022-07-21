#include <math.h>
#include <raylib.h>

#include <algorithm>
#include <iostream>

#include "occupalauney.h"

// Subtraction
Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return {a.x - b.x, a.y - b.y};
}

Vector2 operator-(const Vector2 &a) { return {-a.x, -a.y}; }

// Addition
Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return {a.x + b.x, a.y + b.y};
}

// Division
Vector2 operator/(const Vector2 &a, const float &b) {
    return {a.x / b, a.y / b};
}

// ELement-wise division
Vector2 operator/(const Vector2 &a, const Vector2 &b) {
    return {a.x / b.x, a.y / b.y};
}

// Multiplication
Vector2 operator*(const Vector2 &a, const float &b) {
    return {a.x * b, a.y * b};
}

// Dot product
float operator*(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

Vector2 lerp(const Vector2 &a, const Vector2 &b, const float &t) {
    return a * t + b * (1.0f - t);
}

// Cross product
float operator&(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}

// Returns the magnitude of the vector squared
float magSq(const Vector2 &vec) { return vec.x * vec.x + vec.y * vec.y; }

// Returns the magnitude of the vector
float mag(const Vector2 &vec) { return sqrt(magSq(vec)); }

// Normalizes vector in place and returns it
Vector2 normalize(Vector2 &vec) {
    vec = vec / mag(vec);

    return vec;
}

// returns a normalized version of the vector
Vector2 normalized(const Vector2 &vec) { return vec / mag(vec); }

std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
    os << "V2{ " << v.x << ", " << v.y << " }";
    return os;
}
