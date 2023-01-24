#include "../include/Quaternion.h"

Quaternion::Quaternion()
{
    this->q0 = 0;
    this->q1 = 0;
    this->q2 = 0;
    this->q3 = 0;
}

Quaternion::Quaternion(const Quaternion &quaternion)
{
    this->setQ0(quaternion.q0);
    this->setQ1(quaternion.q1);
    this->setQ2(quaternion.q2);
    this->setQ3(quaternion.q3);
}

Quaternion::Quaternion(double q0, double q1, double q2, double q3)
{
    this->setQ0(q0);
    this->setQ1(q1);
    this->setQ2(q2);
    this->setQ3(q3);
}

Quaternion::~Quaternion()
{
}

double Quaternion::getQ0()
{
    return this->q0;
}

double Quaternion::getQ1()
{
    return this->q1;
}

double Quaternion::getQ2()
{
    return this->q2;
}

double Quaternion::getQ3()
{
    return this->q3;
}

void   Quaternion::setQ0(double q0)
{
    this->q0 = q0;
}

void   Quaternion::setQ1(double q1)
{
    this->q1 = q1;
}

void   Quaternion::setQ2(double q2)
{
    this->q2 = q2;
}

void   Quaternion::setQ3(double q3)
{
    this->q3 = q3;
}

Quaternion Quaternion::getInverse()
{
    Quaternion inverse = Quaternion(this->getQ0(), -this->getQ1(), -this->getQ2(), -this->getQ3());
    return inverse;
}

Quaternion* Quaternion::operator=(Quaternion quaternion)
{
    this->setQ0(quaternion.getQ0());
    this->setQ1(quaternion.getQ1());
    this->setQ2(quaternion.getQ2());
    this->setQ3(quaternion.getQ3());
    return this;
}

Quaternion* Quaternion::operator+(Quaternion quaternion)
{
    this->setQ0(this->getQ0() + quaternion.getQ0());
    this->setQ1(this->getQ1() + quaternion.getQ1());
    this->setQ2(this->getQ2() + quaternion.getQ2());
    this->setQ3(this->getQ3() + quaternion.getQ3());
    return this;
}

Quaternion* Quaternion::operator-(Quaternion quaternion)
{
    this->setQ0(this->getQ0() - quaternion.getQ0());
    this->setQ1(this->getQ1() - quaternion.getQ1());
    this->setQ2(this->getQ2() - quaternion.getQ2());
    this->setQ3(this->getQ3() - quaternion.getQ3());
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
 * 
 * or, more correctly:
 * 
 * t0 = (r0s0 - r1s1 - r2s2 - r3s3)
 * t1 = (r0s1 + r1s0 + r2s3 - r3s2)
 * t2 = (r0s2 - r1s3 + r2s0 + r3s1)
 * t3 = (r0s3 + r1s2 - r2s1 + r3s0)
 **********************************************/
Quaternion Quaternion::operator*(Quaternion quaternion)
{
    this->setQ0(this->getQ0()*quaternion.getQ0() - this->getQ1()*quaternion.getQ1() - this->getQ2()*quaternion.getQ2() - this->getQ3()*quaternion.getQ3());
    this->setQ1(this->getQ0()*quaternion.getQ1() + this->getQ1()*quaternion.getQ0() - this->getQ2()*quaternion.getQ3() + this->getQ3()*quaternion.getQ2());
    this->setQ2(this->getQ0()*quaternion.getQ2() + this->getQ1()*quaternion.getQ3() + this->getQ2()*quaternion.getQ0() - this->getQ3()*quaternion.getQ1());
    this->setQ3(this->getQ0()*quaternion.getQ3() - this->getQ1()*quaternion.getQ2() + this->getQ2()*quaternion.getQ1() + this->getQ3()*quaternion.getQ0());
    return *this;
}
