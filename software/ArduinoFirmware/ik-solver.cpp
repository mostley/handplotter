#include "ik-solver.h"
//#include <stdio.h>

/* cosine rule for angle between c and a */
double return_angle(double a, double b, double c) {
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

double degrees(double radian) {
  return (radian * 180.0) / M_PI;
}

KinematicResult IKSolver::solve(Vector offset) {
    KinematicResult result;

    Vector target = Vector(offset.x + 0.001, offset.y + 0.001) + this->center;
    Vector delta_r = target - this->origin;
    double c = delta_r.length();
    double a1 = atan2(delta_r.x, delta_r.y);
    double a2 = return_angle(this->armLength, this->armLength, c);

    result.leftAngle = 90 - degrees(a1 - a2);
    result.rightAngle = 90 - degrees(a1 + a2);

    // DEBUG:
    // printf("delta_r: [%f, %f] (%f); a1: %f; a2: %f\n", delta_r.x, delta_r.y, c, degrees(a1), degrees(a2));

    return result;
}
