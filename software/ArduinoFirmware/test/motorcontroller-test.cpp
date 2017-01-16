#include <stdio.h>

#include "mocks/BasicStepperDriverMock.cpp"
#include "motorcontroller.cpp"

int test_update() {
  printf("=== Testing MotorController update ===\n");

  BasicStepperDriver stepperLeft(0, 0, 0);
  BasicStepperDriver stepperRight(1, 1, 1);

  MotorController motorcontroller = MotorController(stepperLeft, stepperRight);

  motorcontroller.update(0);

  if (MOCK_ROTATION_RESULT[0] != 0 || MOCK_ROTATION_RESULT[1] != 0) {
    printf("Update failed.\nExpected the resulting Rotation to be [0, 0] ");
    printf("instead got [%f, %f]\n", MOCK_ROTATION_RESULT[0], MOCK_ROTATION_RESULT[1]);
    return 1;
  }

  motorcontroller.updateTargetPosition(KinematicResult(10, 20));

  motorcontroller.update(0);

  if (MOCK_ROTATION_RESULT[0] != 10 || MOCK_ROTATION_RESULT[1] != 20) {
    printf("Update failed.\nExpected the resulting Rotation to be [10, 20] ");
    printf("instead got [%f, %f]\n", MOCK_ROTATION_RESULT[0], MOCK_ROTATION_RESULT[1]);
    return 1;
  }

  motorcontroller.updateTargetPosition(KinematicResult(-10, -20));

  motorcontroller.update(0);

  if (MOCK_ROTATION_RESULT[0] != 0 || MOCK_ROTATION_RESULT[1] != 0) {
    printf("Update failed.\nExpected the resulting Rotation to be [0, 0] ");
    printf("instead got [%f, %f]\n", MOCK_ROTATION_RESULT[0], MOCK_ROTATION_RESULT[1]);
    return 1;
  }

  return 0;
}

int main() {
  int error;

  error = test_update();
  if (error > 0) { return error; }

  return 0;
}
