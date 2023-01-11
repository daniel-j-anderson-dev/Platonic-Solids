#include "../include/Point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(Point *point)
{
    this->x = point->x;
    this->y = point->y;
    this->z = point->z;
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

int Point::getZ()
{
    return this->z;
}

void Point::setX(int x)
{
    this->x = x;
}

void Point::setY(int y)
{
    this->y = y;
}

void Point::setZ(int z)
{
    this->z = z;
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
    this->z++;
}

void Point::increment(int i)
{
    this->x += i;
    this->y += i;
    this->z += i;
}

void Point::rotate(Point point)
{
}