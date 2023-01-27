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
    
    double getX();
    double getY();
    double getZ();
    void   setX(double x);
    void   setY(double y);
    void   setZ(double z);

    Point* operator=(Point point);
    Point* operator+(Point point);
    Point* operator-(Point point);


    //void rotate(Point pointOfRotation, Point axis, double angle);
    Point rotate(Point axis, double angle); // Rotates about SDL's origin

private:

    double x;
    double y;
    double z;

};

#endif