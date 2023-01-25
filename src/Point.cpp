#include "../include/Point.h"
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
    this->setX(point->X());
    this->setY(point->Y());
    this->setZ(point->Z());
}

Point::~Point()
{
}

double Point::X()
{
    return this->x;
}

double Point::Y()
{
    return this->y;
}

double Point::Z()
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

Quaternion Point::toQuaternion()
{
    Quaternion thisPointAsQuaternion = Quaternion(0, this->X(), this->Y(), this->Z());
    return thisPointAsQuaternion;
}

Point* Point::operator=(Point point)
{
    this->x = point.X();
    this->y = point.Y();
    this->z = point.Z();
    return this;
}

Point* Point::operator+(Point point)
{
    this->x += point.X();
    this->y += point.Y();
    this->z += point.Z();
    return this;
}

Point* Point::operator-(Point point)
{
    this->x -= point.X();
    this->y -= point.Y();
    this->z -= point.Z();
    return this;
}


/************************************************************
 * \param pointOfRotation point to rotate this about this will be used
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
    Quaternion rotation = Quaternion(       1 * cos(angle / 2),
                                     axis.X() * sin(angle / 2),
                                     axis.Y() * sin(angle / 2),
                                     axis.Z() * sin(angle / 2));

    Quaternion original = (*this - pointOfRotation)->toQuaternion();

    Quaternion product = rotation.getInverse() * original * rotation;
    
    product = *(product + pointOfRotation.toQuaternion());

    Point rotatedPoint = product.toPoint();

    *this = rotatedPoint;
}