#include <math.h>
#include "vector.cpp"
#include "kinematicresult.cpp"

#ifndef IK_SOLVER_H
#define IK_SOLVER_H

class IKSolver {

private:
  /* the position of the rotation axis of the two arms */
  Vector origin;

  /* the position of the absolute center of the drawing region */
  Vector center;

  double armLength;

public:

  IKSolver(Vector origin, Vector center, double armLength) {
    this->origin = origin;
    this->center = center;
    this->armLength = armLength;
  }

  KinematicResult solve(Vector newPenOffset);
};

#endif  /* IK_SOLVER_H */
