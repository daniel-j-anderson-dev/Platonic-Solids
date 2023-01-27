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
// void Point::rotate(Point pointOfRotation, Point axis, double angle)
// {
//     Quaternion rotation = Quaternion(     1 * cos(angle / 2),
//                                      axis.x * sin(angle / 2),
//                                      axis.y * sin(angle / 2),
//                                      axis.z * sin(angle / 2));

//     Quaternion original = Quaternion(0,
//                                      this->x - pointOfRotation.x,
//                                      this->y - pointOfRotation.y,
//                                      this->z - pointOfRotation.z);

//     Quaternion product = rotation.inverse() * original * rotation;

//     Point rotatedPoint = Point(product.getX() + pointOfRotation.x, product.getY() + pointOfRotation.y, product.getZ() + pointOfRotation.z);

//     *this = rotatedPoint;
// }

Point Point::rotate(Point axis, double angle)
{
    Quaternion rotation = Quaternion(     1 * cos(angle / 2),
                                     axis.x * sin(angle / 2),
                                     axis.y * sin(angle / 2),
                                     axis.z * sin(angle / 2));

    Quaternion original = Quaternion(0, this->x, this->y, this->z);

    Quaternion product = rotation.inverse() * original * rotation;

    Point rotatedPoint = Point(product.getX(), product.getY(), product.getZ());

    return rotatedPoint;
}