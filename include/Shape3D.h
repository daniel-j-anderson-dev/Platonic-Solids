#ifndef SHAPE3D_H
#define SHAPE3D_H
#pragma once
#include "../include/Point.h"
#include <vector>
struct Shape3D
{
    std::vector<Point> vertices;
    std::vector<std::pair<int, int>> edges;
    Point position;
};
#endif