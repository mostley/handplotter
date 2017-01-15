#include <stdio.h>
#include <cmath>

#include "ik-solver.cpp"

const double PRECISION = 0.01;

bool compare(double a, double b) {
  return std::abs(a - b) > PRECISION;
}

int test_solve(Vector target, KinematicResult expectedResult) {
  printf("=== Testing IKSolver with parameters (%.2f:%.2f -> %.2f:%.2f) ===\n", target.x, target.y, expectedResult.leftAngle, expectedResult.rightAngle);
  IKSolver solver = IKSolver(Vector(800, 20), Vector(800, 725), 500);

  KinematicResult actualResult = solver.solve(target);

  if (compare(actualResult.leftAngle,  expectedResult.leftAngle) || compare(actualResult.rightAngle, expectedResult.rightAngle)) {
    printf("Solve failed.\nExpected the resulting KinematicResult to be [%f°, %F°] ", expectedResult.leftAngle, expectedResult.rightAngle);
    printf("instead got [%f, %f]\n", actualResult.leftAngle, actualResult.rightAngle);
    return 1;
  }

  return 0;
}

int main() {
  int error;

  error = test_solve(Vector(70, 70), KinematicResult(123.75, 45.93));
  if (error > 0) { return error; }

  error = test_solve(Vector(-110, -90), KinematicResult(151.48, 48.81));
  if (error > 0) { return error; }

  error = test_solve(Vector(110, -70), KinematicResult(130.05, 30.30));
  if (error > 0) { return error; }

  return 0;
}
