#include <stdio.h>

#include "kinematicresult.cpp"

int test_retention() {
  printf("=== Testing KinematicResult retention ===\n");

  KinematicResult r = KinematicResult(1, 2);

  if (r.leftAngle != 1 || r.rightAngle != 2) {
    printf("Retention failed.\nExpected the resulting KinematicResult to be [1°, 2°] ");
    printf("instead got [%f°, %f°]\n", r.leftAngle, r.rightAngle);
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
