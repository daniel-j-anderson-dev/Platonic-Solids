#include "../include/Transformer.hpp"
#include "Shape3D.hpp"

std::array<Shape3D, 5> platonicSolids() {
    double scale = 50;
    const double PHI = 1.61803398874989484820;
    std::vector<Point> cubeVertices = {
        {scale, scale, scale},   {scale, scale, -scale},
        {scale, -scale, scale},  {scale, -scale, -scale},
        {-scale, scale, scale},  {-scale, scale, -scale},
        {-scale, -scale, scale}, {-scale, -scale, -scale}};
    std::vector<std::pair<int, int>> cubeEdges = {
        {0, 1}, {0, 2}, {0, 4}, {1, 3}, {1, 5}, {2, 3},
        {2, 6}, {3, 7}, {4, 5}, {4, 6}, {5, 7}, {6, 7}};
    Point cubePosition = {0, 0, 0};
    for (auto &vertex : cubeVertices)
        vertex += cubePosition;
    Shape3D cube = {cubeVertices, cubeEdges, cubePosition};

    std::vector<Point> tetrahedronVertices = {{scale, scale, scale},
                                              {-scale, -scale, scale},
                                              {-scale, scale, -scale},
                                              {scale, -scale, -scale}};
    std::vector<std::pair<int, int>> tetrahedronEdges = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    Point tetrahedronPosition = {200, 0, 0};
    for (auto &vertex : tetrahedronVertices)
        vertex += tetrahedronPosition;
    Shape3D tetrahedron = {tetrahedronVertices, tetrahedronEdges,
                           tetrahedronPosition};

    scale *= 1.25; // make the octahedron similar size
    std::vector<Point> octahedronVertices = {{scale, 0, 0}, {-scale, 0, 0},
                                             {0, scale, 0}, {0, -scale, 0},
                                             {0, 0, scale}, {0, 0, -scale}};
    std::vector<std::pair<int, int>> octahedronEdges = {
        {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3},
        {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 4}, {3, 5}};
    Point octahedronPosition = {-200, 0, 0};
    for (auto &vertex : octahedronVertices)
        vertex += octahedronPosition;
    Shape3D octahedron = {octahedronVertices, octahedronEdges,
                          octahedronPosition};

    scale *= .6; // make the dodecah and icosah .75 times scale
    std::vector<Point> dodecahedronVertices = {
        {scale, scale, scale},          {scale, scale, -scale},
        {scale, -scale, scale},         {scale, -scale, -scale},
        {-scale, scale, scale},         {-scale, scale, -scale},
        {-scale, -scale, scale},        {-scale, -scale, -scale},
        {0, scale / PHI, scale * PHI},  {0, scale / PHI, -scale * PHI},
        {0, -scale / PHI, scale * PHI}, {0, -scale / PHI, -scale * PHI},
        {scale / PHI, scale * PHI, 0},  {scale / PHI, -scale * PHI, 0},
        {-scale / PHI, scale * PHI, 0}, {-scale / PHI, -scale * PHI, 0},
        {scale * PHI, 0, scale / PHI},  {scale * PHI, 0, -scale / PHI},
        {-scale * PHI, 0, scale / PHI}, {-scale * PHI, 0, -scale / PHI}};
    std::vector<std::pair<int, int>> dodecahedronEdges = {
        {0, 8},  {0, 12}, {0, 16},  {1, 9},   {1, 12},  {1, 17},
        {2, 10}, {2, 13}, {2, 16},  {3, 11},  {3, 13},  {3, 17},
        {4, 8},  {4, 14}, {4, 18},  {5, 9},   {5, 14},  {5, 19},
        {6, 10}, {6, 15}, {6, 18},  {7, 11},  {7, 15},  {7, 19},
        {8, 10}, {9, 11}, {12, 14}, {13, 15}, {16, 17}, {18, 19}};
    auto dodecahedronPosition = Point{.x = 0, .y = 200, .z = 0};
    for (auto &vertex : dodecahedronVertices)
        vertex += dodecahedronPosition;
    auto dodecahedron = Shape3D{.vertices = dodecahedronVertices,
                                .edges = dodecahedronEdges,
                                .position = dodecahedronPosition};

    std::vector<Point> icosahedronVertices = {
        {0, scale, scale * PHI},  {0, scale, -scale * PHI},
        {0, -scale, scale * PHI}, {0, -scale, -scale * PHI},
        {scale, scale * PHI, 0},  {scale, -scale * PHI, 0},
        {-scale, scale * PHI, 0}, {-scale, -scale * PHI, 0},
        {scale * PHI, 0, scale},  {scale * PHI, 0, -scale},
        {-scale * PHI, 0, scale}, {-scale * PHI, 0, -scale}};
    std::vector<std::pair<int, int>> icosahedronEdges = {
        {0, 2},  {0, 4},  {0, 6},  {0, 8},  {0, 10}, {1, 3},  {1, 4}, {1, 6},
        {1, 9},  {1, 11}, {2, 5},  {2, 7},  {2, 8},  {2, 10}, {3, 5}, {3, 7},
        {3, 9},  {3, 11}, {4, 6},  {4, 8},  {4, 9},  {5, 7},  {5, 8}, {5, 9},
        {6, 10}, {6, 11}, {7, 10}, {7, 11}, {8, 9},  {10, 11}};
    auto icosahedronPosition = Point{.x = 0, .y = -200, .z = 0};
    for (auto &vertex : icosahedronVertices)
        vertex += icosahedronPosition;
    auto icosahedron = Shape3D{.vertices = icosahedronVertices,
                               .edges = icosahedronEdges,
                               .position = icosahedronPosition};

    return {
        cube, tetrahedron, octahedron, dodecahedron, icosahedron,
    };
}

void rotatePoint(Point &point, Point axis, double angle) {
    Quaternion rotation = Quaternion(axis, angle);
    Quaternion original = Quaternion(point);
    Quaternion product = rotation.inverse() * original * rotation;
    auto rotatedPoint =
        Point{.x = product.getX(), .y = product.getY(), .z = product.getZ()};
    point = rotatedPoint;
}

void rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis,
                             double angle) {
    Point difference = point - centerOfRotation;
    rotatePoint(difference, axis, angle);
    Point rotatedPoint = difference + centerOfRotation;
    point = rotatedPoint;
}

void rotateShapeLocal(Shape3D &shape, Point axis, double angle) {
    for (auto &vertex : shape.vertices) {
        rotatePointAboutAnother(vertex, shape.position, axis, angle);
    }
}

void rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis,
                           double angle) {
    for (auto &vertex : shape.vertices) {
        rotatePointAboutAnother(vertex, centerOfRotation, axis, angle);
    }
    rotatePointAboutAnother(shape.position, centerOfRotation, axis, angle);
}

void rotateShapesLocal(std::span<Shape3D> shapes, Point axis, double angle) {
    for (auto &shape : shapes) {
        rotateShapeLocal(shape, axis, angle);
    }
}

void rotateShapesAboutPoint(std::span<Shape3D> shapes, Point centerOfRotation,
                            Point axis, double angle) {
    for (auto &shape : shapes) {
        rotateShapeAboutPoint(shape, centerOfRotation, axis, angle);
    }
}

void translatePoint(Point &point, Point axis, double distance) {
    Point newAxis = {0, 0, 0};
    if (norm(axis) != 0)
        newAxis = axis * distance / norm(axis);
    else
        return;
    point += newAxis;
}

void tanslateShape(Shape3D &shape, Point axis, double distance) {
    for (auto &vertex : shape.vertices) {
        translatePoint(vertex, axis, distance);
    }
    translatePoint(shape.position, axis, distance);
}

void translateShapes(std::span<Shape3D> shapes, Point axis, double distance) {
    for (auto &shape : shapes) {
        tanslateShape(shape, axis, distance);
    }
}

double dotProduct(Point u, Point v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Point crossProduct(Point u, Point v) {
    return Point{.x = u.y * v.z - v.y * u.z,
                 .y = u.z * v.x - v.z * u.x,
                 .z = u.x * v.y - v.x * u.y};
}

double norm(Point point) {
    return sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
}