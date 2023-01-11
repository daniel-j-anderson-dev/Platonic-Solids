#ifndef POINT_H
#define POINT_H

#pragma once

class Point
{
public:
    Point();
    Point(int x, int y, int z);
    Point(Point* point);
    ~Point();
    
    int  getX();
    int  getY();
    int  getZ();
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    void rotate(Point point);

    // replace with operator overload l8r
    void incrementX();
    void incrementY();
    void incrementZ();
    void increment();
    void increment(int i);

private:

    int x;
    int y;
    int z;

};

#endif