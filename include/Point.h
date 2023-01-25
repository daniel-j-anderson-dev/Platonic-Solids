#ifndef POINT_H
#define POINT_H
#pragma once

#include "../include/Quaternion.h"
class Point
{
public:
    Point();
    Point(double x, double y, double z);
    Point(Point* point);
    ~Point();
    
    double X();
    double Y();
    double Z();
    void   setX(double x);
    void   setY(double y);
    void   setZ(double z);

    Quaternion toQuaternion();

    Point* operator=(Point point);
    Point* operator+(Point point);
    Point* operator-(Point point);


    void rotate(Point pointOfRotation, Point axis, double angle);

private:

    double x;
    double y;
    double z;

};

#endif