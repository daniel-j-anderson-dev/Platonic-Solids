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

Point *Point::operator=(Point point)
{
    this->x = point.getX();
    this->y = point.getY();
    this->z = point.getZ();
    return this;
}

Point *Point::operator+(Point point)
{
    this->x += point.getX();
    this->y += point.getY();
    this->z += point.getZ();
    return this;
}

Point *Point::operator-(Point point)
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

    double newX = (x * (1 - 2 * c * c - 2 * d * d) + y * (2 * b * c - 2 * d * a) + z * (2 * b * d + 2 * c * a));
    double newY = (x * (2 * b * c + 2 * d * a) + y * (1 - 2 * b * b - 2 * b * b) + z * (2 * c * d - 2 * b * a));
    double newZ = (x * (2 * b * d - 2 * c * a) + y * (2 * c * d + 2 * b * a) + z * (1 - 2 * b * b - 2 * c * c));

    Point rotatedPoint = Point(newX, newY, newZ);

    std::cout << "x: " << rotatedPoint.getX() << '\t';
    std::cout << "y: " << rotatedPoint.getY() << '\t';
    std::cout << "z: " << rotatedPoint.getZ() << std::endl;

    system("CLS");

    *this = rotatedPoint;

    /*
        
        Rotating a point about a point along an arbitrary axis defined by a vector can be done using quaternions. 
        Quaternions are a mathematical construct that can be used to represent rotations in 3D space. Here's a 
        general process for rotating a point A about point B along an arbitrary axis defined by a vector using quaternions:
        Translate point B to the origin. This can be done by subtracting the coordinates of point B from the 
        coordinates of point A. This will make point B the new origin, and point A will be relative to point B.
        Create a quaternion that represents the rotation. This can be done using the axis-angle representation 
        of a quaternion, where the axis is the arbitrary vector that defines the rotation axis and the angle is 
        the amount of rotation.
        Multiply the quaternion that represents the point A by the quaternion that represents the rotation. 
        This is the quaternion multiplication.
        Convert the result from the quaternion multiplication back into Cartesian coordinates.
        Translate point A back to its original position by adding the coordinates of point B to the coordinates 
        of the rotated point A.
        It is important to note that quaternion multiplication is non-commutative, meaning the order of multiplication 
        matters. Therefore, the order of step 3 is crucial, it should be point times rotation, If rotation quaternion 
        is multiplied with point quaternion, the result will not be correct.
        Another way to achieve the same result is using rotation matrix, you can use the rotation matrix to rotate 
        point A about point B along the arbitrary axis, but quaternion is more computationally efficient when it comes 
        to rotating a large number of points, especially when you are doing rotation in real-time.
        
    */
}
