#include "../include/Quaternion.h"
#include "../include/Point.h"

Quaternion::Quaternion()
{
    this->w = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Quaternion::Quaternion(const Quaternion &q)
{
    this->setW(q.W());
    this->setX(q.X());
    this->setY(q.Y());
    this->setZ(q.Z());
}

Quaternion::Quaternion(double w, double x, double y, double z)
{
    this->setW(w);
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

Quaternion::~Quaternion()
{
}

double Quaternion::W()
{
    return this->w;
}

double Quaternion::X()
{
    return this->x;
}

double Quaternion::Y()
{
    return this->y;
}

double Quaternion::Z()
{
    return this->z;
}

void   Quaternion::setW(double w)
{
    this->w = w;
}

void   Quaternion::setX(double x)
{
    this->x = x;
}

void   Quaternion::setY(double y)
{
    this->y = y;
}

void   Quaternion::setZ(double z)
{
    this->z = z;
}

Quaternion Quaternion::getInverse()
{
    Quaternion inverse = Quaternion(this->W(), -1 * this->X(), -1 * this->Y(), -1 * this->Z());
    return inverse;
}

Point Quaternion::toPoint()
{
    Point thisQuaternionAsPoint = Point(this->X(), this->Y(), this->Z());
    return thisQuaternionAsPoint;
}

Quaternion* Quaternion::operator =(const Quaternion &q)
{
    this->setW(q.W());
    this->setX(q.X());
    this->setY(q.Y());
    this->setZ(q.Z());
    return this;
}

Quaternion* Quaternion::operator +(const Quaternion &q)
{
    this->setW(this->W() + q.W());
    this->setX(this->X() + q.X());
    this->setY(this->Y() + q.Y());
    this->setZ(this->Z() + q.Z());
    return this;
}

Quaternion* Quaternion::operator -(const Quaternion &q)
{
    this->setW(this->W() - q.W());
    this->setX(this->X() - q.X());
    this->setY(this->Y() - q.Y());
    this->setZ(this->Z() - q.Z());
    return this;
}

/**********************************************
 * t is the product of two quaternions r and s
 * 
 * t = rs
 * rs != sr
 * 
 * t0 = (r0s0 − r1s1 − r2s2 − r3s3)
 * t1 = (r0s1 + r1s0 − r2s3 + r3s2)
 * t2 = (r0s2 + r1s3 + r2s0 − r3s1)
 * t3 = (r0s3 − r1s2 + r2s1 + r3s0)
 **********************************************/
Quaternion Quaternion::operator *(const Quaternion &q)
{
    Quaternion product = Quaternion(this->W()*q.W() - this->X()*q.X() - this->Y()*q.Y() - this->Z()*q.Z(),
                                    this->W()*q.X() + this->X()*q.W() + this->Y()*q.Z() - this->Z()*q.Y(),
                                    this->W()*q.Y() - this->X()*q.Z() + this->Y()*q.W() + this->Z()*q.X(),
                                    this->W()*q.Z() + this->X()*q.Y() - this->Y()*q.X() + this->Z()*q.W())
    return product;
}
