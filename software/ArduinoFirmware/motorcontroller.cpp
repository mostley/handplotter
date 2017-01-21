#include "motorcontroller.h"


MotorController::MotorController(BasicStepperDriver stepperLeft, BasicStepperDriver stepperRight)
  :stepperLeft(stepperLeft), stepperRight(stepperRight)
{

  this->stepperLeft.setRPM(120);
  this->stepperLeft.setMicrostep(16);

  this->stepperRight.setRPM(120);
  this->stepperRight.setMicrostep(16);
}

void MotorController::updateTargetPosition(KinematicResult newTargetPosition) {
  this->newTargetPosition = newTargetPosition;
}

void MotorController::update() {
  double leftAngleDelta = this->newTargetPosition.leftAngle - this->currentPosition.leftAngle;
  double rightAngleDelta = this->newTargetPosition.rightAngle - this->currentPosition.rightAngle;

  this->stepperLeft.rotate(leftAngleDelta);
  this->stepperRight.rotate(rightAngleDelta);
  
  this->currentPosition = this->newTargetPosition;
}
