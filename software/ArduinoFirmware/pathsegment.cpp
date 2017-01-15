#include "vector.cpp"

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

};

#endif  /* PATH_SEGMENT_CPP */
