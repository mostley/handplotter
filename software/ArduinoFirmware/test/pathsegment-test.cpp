#include <stdio.h>
#include <cmath>

#include "pathsegment.cpp"
#include "orientation.cpp"

const double PRECISION = 0.01;

bool compare(double a, double b) {
  return std::abs(a - b) > PRECISION;
}

bool compare(Vector a, Vector b) {
  return compare(a.x, b.x) || compare(a.y, b.y);
}

int check_result(PathSegment result, Vector expectedP1, Vector expectedP2) {
    if (compare(result.p1, expectedP1)) {
      printf("reorientation failed.\nExpected the resulting PathSegment.p1 to be [%.2f, %.2f] ", expectedP1.x, expectedP1.y);
      printf("instead got [%f, %f]\n", result.p1.x, result.p1.y);
      return 1;
    }

    if (compare(result.p2, expectedP2)) {
      printf("reorientation failed.\nExpected the resulting PathSegment.p2 to be [%.2f, %.2f] ", expectedP2.x, expectedP2.y);
      printf("instead got [%f, %f]\n", result.p2.x, result.p2.y);
      return 1;
    }

    return 0;
}

int test_retention() {
  printf("=== Testing PathSegment retention ===\n");

  PathSegment a = PathSegment(Vector(1, 2), Vector(3,4));

  if (compare(a.p1, Vector(1, 2)) || compare(a.p2, Vector(3, 4))) {
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
    printf("normalized direction vector test failed.\nExpected the resulting Vector to be [1,0] ");
    printf("instead got [%f, %f]\n", dir.x, dir.y);
    return 1;
  }

  a = PathSegment(Vector(0, 0), Vector(0,5));
  dir = a.getNormalizedDirectionVector();

  if (dir.x != 0 || dir.y != 1) {
    printf("normalized direction vector test failed.\nExpected the resulting Vector to be [0,1] ");
    printf("instead got [%f, %f]\n", dir.x, dir.y);
    return 1;
  }

  return 0;
}

int test_orient() {
  printf("=== Testing PathSegment orientation calculation ===\n");

  PathSegment a = PathSegment(Vector(1, 1), Vector(2, 1));
  PathSegment b = a * Orientation(Vector(0, 0), 90);
  Vector expectedP1 = Vector(1, -1);
  Vector expectedP2 = Vector(1, -2);

  return check_result(b, expectedP1, expectedP2);
}

int main() {
  int error;

  error = test_retention();
  if (error > 0) { return error; }

  error = test_length();
  if (error > 0) { return error; }

  error = test_normdir();
  if (error > 0) { return error; }

  error = test_orient();
  if (error > 0) { return error; }

  return 0;
}
