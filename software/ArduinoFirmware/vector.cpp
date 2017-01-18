#include <math.h>
#include <stdio.h>

#ifndef VECTOR_CPP
#define VECTOR_CPP

struct Vector {

public:
  double x;
  double y;

  Vector() {
    this->x = 0;
    this->y = 0;
  }

  Vector(double x, double y) {
    this->x = x;
    this->y = y;
  }

  Vector add(const Vector& other) {
    return Vector(this->x + other.x, this->y + other.y);
  }

  Vector substract(const Vector& other) {
    return Vector(this->x - other.x, this->y - other.y);
  }

  Vector multiply(double other) {
    return Vector(this->x * other, this->y * other);
  }

  Vector divide(double other) {
    return Vector(this->x / other, this->y / other);
  }

  void rotate(double angle) {
    /*  x' = x cos f - y sin f
        y' = y cos f + x sin f  */
    double radAngle = angle * M_PI/180.0;
    double radAngle2 = 60 * M_PI / 180.0;
    printf("%f -> %f  %f -> %f\n", radAngle, sin(radAngle), radAngle2, sin ( radAngle2 ));

    double sinRadAngle = sin(radAngle);
    double cosRadAngle = cos(radAngle);
    double x = this->x;
    double y = this->y;
    this->x = x * cosRadAngle - y * sinRadAngle;
    this->y = y * cosRadAngle + x * sinRadAngle;
  }

  double length() {
    return sqrt(this->x * this->x + this->y * this->y);
  }

  Vector operator+(const Vector& b) {
    return this->add(b);
  }

  Vector operator-(const Vector& b) {
    return this->substract(b);
  }

  Vector operator*(double b) {
    return this->multiply(b);
  }

  Vector operator/(double b) {
    return this->divide(b);
  }
};

#endif  /* VECTOR_CPP */
