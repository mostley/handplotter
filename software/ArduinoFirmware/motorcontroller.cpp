#include "motorcontroller.h"


MotorController::MotorController(BasicStepperDriver stepperLeft, BasicStepperDriver stepperRight)
  :stepperLeft(stepperLeft), stepperRight(stepperRight)
{

  this->stepperLeft.setRPM(120);
  this->stepperLeft.setMicrostep(16);

  this->stepperRight.setRPM(120);
  this->stepperRight.setMicrostep(16);
  //DRV8825 stepper(MOTOR_STEPS, DIR, STEP, MODE0, MODE1, MODE2);
}

void MotorController::updateTargetPosition(KinematicResult newTargetPosition) {
  this->newTargetPosition = newTargetPosition;
}

void MotorController::update(double deltaTime) {
  double leftAngleDelta = this->newTargetPosition.leftAngle - this->currentPosition.leftAngle;
  double rightAngleDelta = this->newTargetPosition.rightAngle - this->currentPosition.rightAngle;

  this->stepperLeft.rotate((int)leftAngleDelta);
  this->stepperRight.rotate((int)rightAngleDelta);
}
