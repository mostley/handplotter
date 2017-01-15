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

  Vector operator+(const Vector& b) {
    return this->add(b);
  }

  Vector operator-(const Vector& b) {
    return this->substract(b);
  }

  Vector operator*(double b) {
    return this->multiply(b);
  }
};

#endif  /* VECTOR_CPP */
