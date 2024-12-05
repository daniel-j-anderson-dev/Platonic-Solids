#include "../include/Quaternion.hpp"
#include <cmath>

Quaternion::Quaternion() {
  this->w = 0;
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Quaternion::Quaternion(double w, double x, double y, double z) {
  this->setW(w);
  this->setX(x);
  this->setY(y);
  this->setZ(z);
}

Quaternion::Quaternion(Point axis, double angle) {
  this->setW(1 * cos(angle / 2));
  this->setX(axis.x * sin(angle / 2));
  this->setY(axis.y * sin(angle / 2));
  this->setZ(axis.z * sin(angle / 2));
}

Quaternion::Quaternion(Point point) {
  this->setW(0);
  this->setX(point.x);
  this->setY(point.y);
  this->setZ(point.z);
}

Quaternion::~Quaternion() {}

double Quaternion::getW() { return this->w; }

double Quaternion::getX() { return this->x; }

double Quaternion::getY() { return this->y; }

double Quaternion::getZ() { return this->z; }

double Quaternion::getAngle() { return acos(this->getW() * 2); }

Point Quaternion::getAxis() {
  return {this->getX() / sin(this->getAngle()),
          this->getY() / sin(this->getAngle()),
          this->getZ() / sin(this->getAngle())};
}

void Quaternion::setW(double w) { this->w = w; }

void Quaternion::setX(double x) { this->x = x; }

void Quaternion::setY(double y) { this->y = y; }

void Quaternion::setZ(double z) { this->z = z; }

double Quaternion::norm() {
  double w2 = this->w * this->w;
  double x2 = this->x * this->x;
  double y2 = this->y * this->y;
  double z2 = this->z * this->z;
  return sqrt(w2 + x2 + y2 + z2);
}

Quaternion Quaternion::conjugate() {
  return Quaternion(this->w, -1 * this->x, -1 * this->y, -1 * this->z);
}

Quaternion Quaternion::inverse() {
  double norm2 = this->norm() * this->norm();
  Quaternion conj = this->conjugate();
  return Quaternion(conj.w / norm2, conj.x / norm2, conj.y / norm2,
                    conj.z / norm2);
}

Quaternion *Quaternion::operator=(const Quaternion &q) {
  this->setW(q.w);
  this->setX(q.x);
  this->setY(q.y);
  this->setZ(q.z);
  return this;
}

Quaternion *Quaternion::operator+(const Quaternion &q) {
  this->setW(this->w + q.w);
  this->setX(this->x + q.x);
  this->setY(this->y + q.y);
  this->setZ(this->z + q.z);
  return this;
}

Quaternion *Quaternion::operator-(const Quaternion &q) {
  this->setW(this->w - q.w);
  this->setX(this->x - q.x);
  this->setY(this->y - q.y);
  this->setZ(this->z - q.z);
  return this;
}

Quaternion Quaternion::operator*(const Quaternion &q) {
  Quaternion product =
      Quaternion(this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z,
                 this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
                 this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,
                 this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w);
  return product;
}