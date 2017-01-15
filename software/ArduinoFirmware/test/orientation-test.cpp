#include <stdio.h>

#include "orientation.cpp"

int test_retention() {
  printf("=== Testing Orientation retention ===\n");

  Orientation orientation = Orientation(Vector(15, 25), 45);

  if (orientation.position.x != 15 || orientation.position.y != 25 || orientation.rotation != 45) {
    printf("Retention failed. expected [15, 25, 45°]\n");
    printf("instead got [%f, %f, %f°]\n", orientation.position.x, orientation.position.y, orientation.rotation);
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
