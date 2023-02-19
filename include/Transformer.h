#ifndef TRANSFORMER_H
#define TRANSFORMER_H
#pragma once
#include "../include/Point.h"
#include "../include/Shape3D.h"
#include "../include/Quaternion.h"
#include <cmath>

class Transformer
{
public:
    Transformer();
    ~Transformer();

    void rotatePoint(Point &point, Point axis, double angle);
    void rotatePointAboutAnother(Point &point, Point centerOfRotation, Point axis, double angle);
    void  rotateShapeLocal(Shape3D &shape, Point axis, double angle);
    void  rotateShapeAboutPoint(Shape3D &shape, Point centerOfRotation, Point axis, double angle);
    template <int size>
    void  rotateShapesLocal(Shape3D (&shapes)[size], Point axis, double angle);
    template <int size>
    void  rotateShapesAboutPoint(Shape3D (&shapes)[size],Point centerOfRotation, Point axis, double angle);

    void translatePoint(Point &point, Point axis, double distance);
    void  tanslateShape(Shape3D &shape, Point axis, double distance);
    template <int size>
    void  translateShapes(Shape3D (&shapes)[size], Point axis, double distance);

private:
};

#endif