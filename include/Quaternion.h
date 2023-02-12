#ifndef QUATERNION_H
#define QUATERNION_H
#pragma once

#include "../include/Point.h"

class Quaternion
{
public:

    Quaternion();
    Quaternion(double w, double x, double y, double z);
    Quaternion(Point axis, double angle);
    Quaternion(Point point);
    ~Quaternion();
    
    double getW();
    double getX();
    double getY();
    double getZ();
    
    void   setW(double w);
    void   setX(double x);
    void   setY(double y);
    void   setZ(double z);
    
    double     norm();
    Quaternion conjugate();
    Quaternion inverse();

    Quaternion* operator =(const Quaternion &q);
    Quaternion* operator +(const Quaternion &q);
    Quaternion* operator -(const Quaternion &q);
    Quaternion  operator *(const Quaternion &q);

private:

    double w;
    double x;
    double y;
    double z;

};

#endif