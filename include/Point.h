#ifndef POINT_H
#define POINT_H

#pragma once

class Point
{
public:
    Point();
    Point(int x, int y);
    Point(Point* point);
    ~Point();
    
    int  getX();
    int  getY();
    void setX(int x);
    void setY(int y);

    void incX();
    void incY();
    void inc();
    void inc(int i);

private:

    int x;
    int y;

};

#endif