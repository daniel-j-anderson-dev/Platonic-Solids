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

    // equal operator overload
    Point* operator=(Point point);
    Point* operator+(Point point);
    Point* operator-(Point point);

    // Rotates this about podouble with an
    // this function acts on a podouble P.
    // it will rotate P angle degrees about an arbitrary axis
    // given by a normalized vector and the origin

    // I want to store the axis as one variable
    // I dont want to use a podouble to represent the axis because it uses ints
    // which would lock me in to integer multiples of angles
    // I dont use doubles in the podouble class becasue the sdl draw funciton wants ints

    // I could make the Podouble class use doubles and cast to double to draw

    void rotate(Point point, Point axis, double angle);

    // replace with operator overload l8r
    void incrementX();
    void incrementY();
    void incrementZ();
    void increment();
    void increment(double i);

private:

    double x;
    double y;
    double z;

};

#endif