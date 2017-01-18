#include "vector.cpp"
#include "Orientation.cpp"

#ifndef PATH_SEGMENT_CPP
#define PATH_SEGMENT_CPP

struct PathSegment {

public:
  Vector p1;
  Vector p2;

  PathSegment() {
    this->p1 = Vector();
    this->p2 = Vector();
  }

  PathSegment(Vector p1, Vector p2) {
    this->p1 = p1;
    this->p2 = p2;
  }

  void translate() {}

  void rotate() {}

  double length() {
    return (p2 - p1).length();
  }

  Vector getNormalizedDirectionVector() {
    Vector direction = p2 - p1;
    return direction / direction.length();
  }

  PathSegment operator*(Orientation orientation) {
    Vector p1 = orientation.position - this->p1;
    Vector p2 = orientation.position - this->p2;
    p1.rotate(orientation.rotation);
    p2.rotate(orientation.rotation);
    return PathSegment(p1, p2);
  }
};

#endif  /* PATH_SEGMENT_CPP */
