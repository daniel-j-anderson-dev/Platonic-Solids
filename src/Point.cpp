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

void Point::incrementX()
{
    this->x++;
}

void Point::incrementY()
{
    this->y++;
}

void Point::increment()
{
    this->x++;
    this->y++;
}

void Point::increment(int i)
{
    this->x += i;
    this->y += i;
}