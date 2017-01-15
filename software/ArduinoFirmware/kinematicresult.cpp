#ifndef KINEMATIC_RESULT_CPP
#define KINEMATIC_RESULT_CPP

struct KinematicResult {

public:
  double leftAngle;
  double rightAngle;

  KinematicResult() {
    this->leftAngle = 0;
    this->rightAngle = 0;
  }

  KinematicResult(double leftAngle, double rightAngle) {
    this->leftAngle = leftAngle;
    this->rightAngle = rightAngle;
  }
};

#endif  /* KINEMATIC_RESULT_CPP */
