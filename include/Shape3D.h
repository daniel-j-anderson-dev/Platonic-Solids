#ifndef SHAPE3D_H
#define SHAPE3D_H
#pragma once

#include <vector>
#include "../include/Point.h"

class Shape3D
{
public:

    Shape3D();
    ~Shape3D();

    void addVertex(Point vertex);
    void addEdge(int firstVertexIndex, int secondVertexIndex);

    void removeVertex(int index);
    void removeEdge(int index);

private:

    std::vector<Point> vertices;
    std::vector<std::pair<int, int>> edges;

};

#endif