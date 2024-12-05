#ifndef POINT_HPP
#define POINT_HPP
#pragma once

struct Point {
    double x;
    double y;
    double z;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    Point operator+(const Point &other) const {
        return Point{x + other.x, y + other.y, z + other.z};
    }

    Point operator-(const Point &other) const {
        return Point{x - other.x, y - other.y, z - other.z};
    }

    Point operator*(double scalar) const {
        return Point{x * scalar, y * scalar, z * scalar};
    }

    Point operator/(double scalar) const {
        return Point{x / scalar, y / scalar, z / scalar};
    }
    Point &operator+=(const Point &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Point &operator-=(const Point &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Point &operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    Point &operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};
#endif