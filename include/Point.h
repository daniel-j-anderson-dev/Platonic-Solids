#ifndef POINT_H
#define POINT_H

#pragma once

class Point
{
public:
    Point();
    Point(double x, double y);
    Point(Point* point);
    ~Point();
    
    double getX();
    double getY();
    void   setX(double x);
    void   setY(double y);


private:

    // Change these to ints
    double x;
    double y;

};

#endif