#include "vector.cpp"

#ifndef ORIENTATION_CPP
#define ORIENTATION_CPP

class Orientation {
public:
  Vector position;
  double rotation;

  Orientation() {
    this->position = Vector(0, 0);
    this->rotation = 0;
  }

  Orientation(Vector position, double rotation) {
    this->position = position;
    this->rotation = rotation;
  }
};

#endif  /* ORIENTATION_CPP */
