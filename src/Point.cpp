#include "../include/Point.h"
#include <cmath>

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

Point::Point(Point *point)
{
    this->setX(point->getX());
    this->setY(point->getY());
    this->setZ(point->getZ());
}

Point::~Point()
{
}

double Point::getX()
{
    return this->x;
}

double Point::getY()
{
    return this->y;
}

double Point::getZ()
{
    return this->z;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

void Point::setZ(double z)
{
    this->z = z;
}

void Point::setXYZ(double x, double y, double z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

Point* Point::operator=(Point point)
{
    this->x = point.getX();
    this->y = point.getY();
    this->z = point.getZ();
    return this;
}

Point Point::operator+(Point point)
{
    this->x += point.getX();
    this->y += point.getY();
    this->z += point.getZ();
    return this;
}

Point Point::operator-(Point point)
{
    this->x -= point.getX();
    this->y -= point.getY();
    this->z -= point.getZ();
    return this;
}

void Point::incX()
{
    this->setX(this->getX() + 1);
}

void Point::incY()
{
    this->setY(this->getY() + 1);
}

void Point::incZ()
{
    this->setZ(this->getZ() + 1);
}

void Point::decX()
{
    this->setX(this->getX() - 1);
}

void Point::decY()
{
    this->setY(this->getY() - 1);
}

void Point::decZ()
{
    this->setZ(this->getZ() - 1);
}

void Point::incXYZ()
{
    this->setXYZ(this->getX() + 1, this->getY() + 1, this->getZ() + 1);
}

void Point::decXYZ()
{
    this->setXYZ(this->getX() - 1, this->getY() - 1, this->getZ() - 1);
}