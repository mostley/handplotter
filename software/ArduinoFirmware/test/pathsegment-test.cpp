#include <stdio.h>

#include "pathsegment.cpp"

int test_retention() {
  printf("=== Testing PathSegment retention ===\n");

  PathSegment a = PathSegment(Vector(1, 2), Vector(3,4));

  if (a.p1.x != 1 || a.p1.y != 2 || a.p2.x != 3 || a.p2.y != 4) {
    printf("Retention failed.\nExpected the resulting PathSegment to be [[1, 2], [3, 4]] ");
    printf("instead got [[%f, %f], [%f, %f]]\n", a.p1.x, a.p1.y, a.p2.x, a.p2.y);
    return 1;
  }

  return 0;
}

int test_length() {
  printf("=== Testing PathSegment Length calculation ===\n");

  PathSegment a = PathSegment(Vector(1, 2), Vector(2,2));
  double length = a.length();

  if (length != 1) {
    printf("Length calculation failed.\nExpected the resulting PathSegment to be of length 1 ");
    printf("instead got %f\n", length);
    return 1;
  }

  a = PathSegment(Vector(2, 2), Vector(2,4));
  length = a.length();

  if (length != 2) {
    printf("Length calculation failed.\nExpected the resulting length 2 ");
    printf("instead got %f\n", length);
    return 1;
  }

  return 0;
}

int test_normdir() {
  printf("=== Testing PathSegment normalized direction calculation ===\n");

  PathSegment a = PathSegment(Vector(1, 0), Vector(5,0));
  Vector dir = a.getNormalizedDirectionVector();

  if (dir.x != 1 || dir.y != 0) {
    printf("normalized direction vector test failed.\nExpected the resulting Vector to be [1,1] ");
    printf("instead got [%f, %f]\n", dir.x, dir.y);
    return 1;
  }

  return 0;
}

int main() {
  int error;

  error = test_retention();
  if (error > 0) { return error; }

  error = test_length();
  if (error > 0) { return error; }

  error = test_normdir();
  if (error > 0) { return error; }

  return 0;
}
