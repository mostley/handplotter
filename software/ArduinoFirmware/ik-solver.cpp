#include "ik-solver.h"

/* cosine rule for angle between c and a */
double return_angle(double a, double b, double c) {
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

double degrees(double radian) {
  return radian * M_PI / 180.0;
}

KinematicResult IKSolver::solve(Vector target) {
    KinematicResult result;

    Vector delta_r = target - this->origin;
    double c = delta_r.length();
    double a1 = atan2(delta_r.x, delta_r.y);
    double a2 = return_angle(this->armLength, this->armLength, c);

    result.leftAngle = 90 - degrees(a1 - a2);
    result.rightAngle = 90 - degrees(a1 + a2);

    return result;
}
