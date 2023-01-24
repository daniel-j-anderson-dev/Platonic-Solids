#include "../include/Point.h"
#include "../include/Quaternion.h"
#include <cmath>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>

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

Point* Point::operator=(Point point)
{
    this->x = point.getX();
    this->y = point.getY();
    this->z = point.getZ();
    return this;
}

Point* Point::operator+(Point point)
{
    this->x += point.getX();
    this->y += point.getY();
    this->z += point.getZ();
    return this;
}

Point* Point::operator-(Point point)
{
    this->x -= point.getX();
    this->y -= point.getY();
    this->z -= point.getZ();
    return this;
}

Point* Point::operator*(Point point)
{
    this->x *= point.getX();
    this->y *= point.getY();
    this->z *= point.getZ();
    return this;
}

Point* Point::operator/(Point point)
{
    this->x /= point.getX();
    this->y /= point.getY();
    this->z /= point.getZ();
    return this;
}

/************************************************************
 * \param point point to rotate this about this will be used
 *              to translate to the origin for calculation
 * \param aixs  UNIT vector representing the axis of rotation
 *              (THE NORM OF THIS MUST BE EQUAL TO 1)
 * \param angle amount to rotate this about axis
 * 
 * This function will create a rotation quaternion based on
 * the the axis and angle, and translate the this and point
 ************************************************************/
void Point::rotate(Point pointOfRotation, Point axis, double angle)
{
    Quaternion rotation = Quaternion(          1 * cos(angle / 2),
                                     axis.getX() * sin(angle / 2),
                                     axis.getY() * sin(angle / 2),
                                     axis.getZ() * sin(angle / 2));
    
    Quaternion original = Quaternion(0,
                                     this->getX() - pointOfRotation.getX(),
                                     this->getY() - pointOfRotation.getY(),
                                     this->getZ() - pointOfRotation.getZ());
    //O'=R.inverse * original * R

    Quaternion product = rotation.getInverse() * original * rotation;

    Point rotatedPoint = Point(product.getQ1() + pointOfRotation.getX(),
                               product.getQ2() + pointOfRotation.getY(),
                               product.getQ3() + pointOfRotation.getZ());

    *this = rotatedPoint;
}