#include "vector.cpp"
#include "kinematicresult.cpp"
#include <cmath>
#include "StepperDriver/BasicStepperDriver.h"

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class MotorController {
private:

  KinematicResult currentPosition;
  KinematicResult newTargetPosition;
  BasicStepperDriver stepperLeft;
  BasicStepperDriver stepperRight;

public:

  MotorController(BasicStepperDriver stepperLeft, BasicStepperDriver stepperRight);

  void updateTargetPosition(KinematicResult newTargetPosition);

  void update(double deltaTime);
};

#endif  /* MOTOR_CONTROLLER_H */
