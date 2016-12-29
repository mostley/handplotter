#include "vector.h"

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

class MotorController {
private:

  Vector currentPenOffset;

public:

  MotorController(double stepsPerMM);

  void updatePenOffset(Vector newPenOffset);

  void update(double deltaTime);
}

#endif  /* MOTOR_CONTROLLER_H */
