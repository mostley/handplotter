#include <stdio.h>

#include "ik-solver.cpp"

int test_simple_solve() {
  printf("=== Testing IKSolver retention ===\n");

  IKSolver solver = IKSolver(Vector(0, 20), 500);

  KinematicResult result = solver.solve(Vector(0,0));

  if (result.leftAngle != 0 || result.rightAngle != 0) {
    printf("Retention failed.\nExpected the resulting IKSolver to be [0°, 0°] ");
    printf("instead got [%f, %f]\n", result.leftAngle, result.rightAngle);
    return 1;
  }

  return 0;
}

int main() {
  int error;

  error = test_simple_solve();
  if (error > 0) { return error; }

  return 0;
}
