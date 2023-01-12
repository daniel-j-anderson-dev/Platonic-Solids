#include "../include/Point.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z)
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

void Point::rotate(Point point, Point axis, double angle)
{
    // define the four seperate parts of a quaternion
    // i need the real part, and the i, j, and k coefficients
    // they will be represnted as four separate variables

    /*  angle = math.radians(angle)
        x, y, z = point[0], point[1], point[2]
        a = 1 * math.cos(angle/2)
        b = axis[0] * math.sin(angle/2)
        c = axis[1] * math.sin(angle/2)
        d = axis[2] * math.sin(angle/2)
        return [(x*(1 - 2*c**2 - 2*d**2) + y*(2*b*c - 2*d*a) + z*(2*b*d + 2*c*a)),
                (x*(2*b * c + 2*d*a) + y*(1 - 2*b**2 - 2*d**2) + z*(2*c*d - 2*b*a)),
                (x*(2*b * d - 2*c*a) + y*(2*c*d + 2*b*a) + z*(1 - 2*b**2 - 2*c**2))]
    */
    angle /= 2;

    double x = point.getX();
    double y = point.getY();
    double z = point.getZ();

    double a = cos(angle);
    double b = axis.getX() * sin(angle);
    double c = axis.getY() * sin(angle);
    double d = axis.getZ() * sin(angle);

    Point rotatedPoint = Point((x * (1 - 2 * pow(c, 2) - 2 * pow(d, 2)) + y * (2 * b * c - 2 * d * a)             + z * (2 * b * d + 2 * c * a)),
                               (x * (2 * b * c + 2 * d * a)             + y * (1 - 2 * pow(b, 2) - 2 * pow(d, 2)) + z * (2 * c * d - 2 * b * a)),
                               (x * (2 * b * d - 2 * c * a)             + y * (2 * c * d + 2 * b * a)             + z * (1 - 2 * pow(b, 2) - 2 * pow(c, 2))));
    
    std::cout << "x: " << rotatedPoint.getX() << '\t';
    std::cout << "y: " << rotatedPoint.getY() << '\t';
    std::cout << "z: " << rotatedPoint.getZ() << std::endl;

    system("CLS");

    *this = rotatedPoint;
}

