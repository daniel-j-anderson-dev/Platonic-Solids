#ifndef SHAPE3D_H
#define SHAPE3D_H
#pragma once

#include "../include/SDL2/SDL.h"
#include "../include/Point.h"
#include <cmath>
#include <vector>
#include <string>

class Shape3D
{
public:

    Shape3D(std::string platonicSolid);
    Shape3D();
    ~Shape3D();

    void addVertex(Point vertex);
    void addEdge(int firstVertexIndex, int secondVertexIndex);

    void removeVertex(int index);
    void removeEdge(int index);

    void draw(SDL_Renderer* renderer, Point ORIGIN);
    void rotate(Point axis, double angle);

private:

    std::vector<Point> vertices;
    std::vector<std::pair<int, int>> edges;
    Point position;
};

#endif