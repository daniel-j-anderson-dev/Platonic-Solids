#ifndef SHAPE3D_H
#define SHAPE3D_H
#pragma once

#include "../include/Point.h"
#include <cmath>
#include <vector>

class Shape3D
{
public:

    Shape3D(int platonicSolidID);
    Shape3D();
    ~Shape3D();

    void addVertex(Point vertex);
    void addEdge(int firstVertexIndex, int secondVertexIndex);

    void removeVertex(int index);
    void removeEdge(int index);

    int  numberOfEdges();
    int  numberOfVertices();

    std::vector<Point> vertices;
    std::vector<std::pair<int, int>> edges;
    Point position;
};

#endif