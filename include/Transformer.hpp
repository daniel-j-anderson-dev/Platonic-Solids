#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP
#include <array>
#include <span>
#pragma once
#include "../include/Point.hpp"
#include "../include/Quaternion.hpp"
#include "../include/Renderer.hpp"
#include "../include/Shape3D.hpp"
#include <cmath>

std::array<Shape3D, 5> platonicSolids();
void rotatePoint(Point &point, Point axis, double angle);
void rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis,
                             double angle);
void rotateShapeLocal(Shape3D &shape, Point axis, double angle);
void rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis,
                           double angle);
void rotateShapesLocal(std::span<Shape3D> shapes, Point axis, double angle);
void rotateShapesAboutPoint(std::span<Shape3D> shapes, Point centerOfRotation,
                            Point axis, double angle);

void translatePoint(Point &point, Point axis, double distance);
void tanslateShape(Shape3D &shape, Point axis, double distance);
void translateShapes(std::span<Shape3D> shapes, Point axis, double distance);

double dotProduct(Point u, Point v);
Point crossProduct(Point u, Point v);
double norm(Point point);

#endif