#ifndef POINT_H
#define POINT_H
#pragma once


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
    void   setXYZ(double x, double y, double z);

    void   incX();
    void   incY();
    void   incZ();
    void   decX();
    void   decY();
    void   decZ();
    void   incXYZ();
    void   decXYZ();

    

    Point* operator=(Point point);
    Point operator+(Point point);
    Point operator-(Point point);

private:

    double x;
    double y;
    double z;
};

#endif