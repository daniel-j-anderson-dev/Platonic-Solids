#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

class Quaternion
{
public:
    Quaternion();
    Quaternion(Quaternion* quaternion);
    Quaternion(double q0, double q1, double q2, double q3);
    ~Quaternion();
    
    double getQ0();
    double getQ1();
    double getQ2();
    double getQ3();
    void   setQ0(double Q0);
    void   setQ1(double Q1);
    void   setQ2(double Q2);
    void   setQ3(double Q3);
    Quaternion getInverse();

    Quaternion* operator=(Quaternion quaternion);
    Quaternion* operator+(Quaternion quaternion);
    Quaternion* operator-(Quaternion quaternion);
    Quaternion* operator*(Quaternion quaternion);
    Quaternion* operator/(Quaternion quaternion);

private:

    double q0;
    double q1;
    double q2;
    double q3;

};

#endif