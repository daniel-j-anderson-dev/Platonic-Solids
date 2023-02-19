#ifndef TRANSFORMER_H
#define TRANSFORMER_H
#pragma once
#include "../include/Point.h"
#include "../include/Shape3D.h"
#include "../include/Quaternion.h"
#include <cmath>

std::vector<Shape3D> platonicSolids();
void rotatePoint(Point &point, Point axis, double angle);
void rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis, double angle);
void rotateShapeLocal(Shape3D &shape, Point axis, double angle);
void rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle);
void rotateShapesLocal(std::vector<Shape3D> &shapes, Point axis, double angle);
void rotateShapesAboutPoint(std::vector<Shape3D> &shapes,Point centerOfRotation, Point axis, double angle);

void translatePoint(Point &point, Point axis, double distance);
void tanslateShape(Shape3D &shape, Point axis, double distance);
void translateShapes(std::vector<Shape3D> &shapes, Point axis, double distance);

#endif