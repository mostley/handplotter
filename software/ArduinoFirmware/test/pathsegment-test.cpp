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

int main() {
  int error;

  error = test_retention();
  if (error > 0) { return error; }

  return 0;
}
