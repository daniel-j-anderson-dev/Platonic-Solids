#include "../include/Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point(Point* point)
{
    this->x = point->x;
    this->y = point->y;
}

Point::~Point()
{
    
}

int Point::getX()
{
    return this->x;
}

int Point::getY()
{
    return this->y;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}

void Point::incX()
{
    this->x++;
}

void Point::incY()
{
    this->y++;
}

void Point::inc()
{
    this->x++;
    this->y++;
}

void Point::inc(int i)
{
    this->x += i;
    this->y += i;
}