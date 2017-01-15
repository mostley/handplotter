#include "vector.h"

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class MotorController {
private:

  Vector newTargetPosition;

public:

  MotorController(double stepsPerMM);

  void updateOrientation(Vector newTargetPosition);

  void update(double deltaTime);
}

#endif  /* MOTOR_CONTROLLER_H */
