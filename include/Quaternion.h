#ifndef QUATERNION_H
#define QUATERNION_H
#pragma once

#include "../include/Point.h"

class Quaternion
{
public:

    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(double w, double x, double y, double z);
    ~Quaternion();
    
    double W();
    double X();
    double Y();
    double Z();
    void   setW(double w);
    void   setX(double x);
    void   setY(double y);
    void   setZ(double z);
    
    Quaternion   getInverse();
    Point toPoint();

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