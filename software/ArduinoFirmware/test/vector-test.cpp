#include <stdio.h>

#include "vector.cpp"

int test_retention() {
  printf("=== Testing Vector retention ===\n");

  Vector vector = Vector(15, 25);
  if (vector.x != 15) {
    printf("Retention failed. X was not saved in constructor\n");
    return 1;
  }

  if (vector.y != 25) {
    printf("Retention failed. Y was not saved in constructor\n");
    return 1;
  }

  return 0;
}

int test_addition() {
  printf("=== Testing Vector addition ===\n");

  Vector a = Vector(5, 10);
  Vector b = Vector(10, 20);
  Vector c = a + b;

  if (c.x != 15 || c.y != 30) {
    printf("Addition failed.\nExpected the resulting Vector to be [15, 30] ");
    printf("instead got [%f, %f]\n", c.x, c.y);
    return 1;
  }

  return 0;
}

int test_substraction() {
  printf("=== Testing Vector substraction ===\n");

  Vector a = Vector(5, 10);
  Vector b = Vector(10, 2);
  Vector c = a - b;

  if (c.x != -5 || c.y != 8) {
    printf("Substraction failed.\nExpected the resulting Vector to be [-5, 5] ");
    printf("instead got [%f, %f]\n", c.x, c.y);
    return 1;
  }

  return 0;
}

int test_multiplication() {
  printf("=== Testing Vector multiplication ===\n");

  Vector a = Vector(4, 10);
  double b = 1.5;
  Vector c = a * b;

  if (c.x != 6 || c.y != 15) {
    printf("Multiplication with double failed.\nExpected the resulting Vector to be [6, 15] ");
    printf("instead got [%f, %f]\n", c.x, c.y);
    return 1;
  }

  int d = 2;
  c = a * d;

  if (c.x != 8 || c.y != 20) {
    printf("Multiplication with double failed.\nExpected the resulting Vector to be [8, 20] ");
    printf("instead got [%f, %f]\n", c.x, c.y);
    return 1;
  }

  return 0;
}

int test_division() {
  printf("=== Testing Vector Division ===\n");

  Vector a = Vector(4, 10);
  double b = 2;
  Vector c = a / b;

  if (c.x != 2 || c.y != 5) {
    printf("Division with double failed.\nExpected the resulting Vector to be [2, 5] ");
    printf("instead got [%f, %f]\n", c.x, c.y);
    return 1;
  }

  return 0;
}

int test_length() {
  printf("=== Testing Vector length calculation ===\n");

  Vector a = Vector(3, 4);
  double c = a.length();

  if (c != 5) {
    printf("Length calculation failed.\nExpected the resulting Vector to be 5 ");
    printf("instead got %f\n", c);
    return 1;
  }

  return 0;
}

int main() {
  int error;

  error = test_retention();
  if (error > 0) { return error; }

  error = test_addition();
  if (error > 0) { return error; }

  error = test_substraction();
  if (error > 0) { return error; }

  error = test_multiplication();
  if (error > 0) { return error; }

  error = test_division();
  if (error > 0) { return error; }

  return 0;
}
