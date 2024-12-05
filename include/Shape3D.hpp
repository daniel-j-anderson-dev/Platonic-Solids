#ifndef SHAPE3D_HPP
#define SHAPE3D_HPP
#pragma once
#include "../include/Point.hpp"
#include <vector>
struct Shape3D
{
    std::vector<Point> vertices;
    std::vector<std::pair<int, int>> edges;
    Point position;
};
#endif